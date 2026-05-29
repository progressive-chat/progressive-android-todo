/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.call

import com.airbnb.mvrx.Fail
import com.airbnb.mvrx.Loading
import com.airbnb.mvrx.MavericksViewModelFactory
import com.airbnb.mvrx.Success
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.core.di.MavericksAssistedViewModelFactory
import chat.progressive.app.core.di.hiltMavericksViewModelFactory
import chat.progressive.app.core.platform.ProgressiveViewModel
import chat.progressive.app.features.call.audio.CallAudioManager
import chat.progressive.app.features.call.dialpad.DialPadLookup
import chat.progressive.app.features.call.transfer.CallTransferResult
import chat.progressive.app.features.call.webrtc.WebRtcCall
import chat.progressive.app.features.call.webrtc.WebRtcCallManager
import chat.progressive.app.features.call.webrtc.getOpponentAsMatrixItem
import chat.progressive.app.features.createdirect.DirectRoomHelper
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import org.matrix.android.sdk.api.MatrixPatterns
import org.matrix.android.sdk.api.extensions.orFalse
import org.matrix.android.sdk.api.session.Session
import org.matrix.android.sdk.api.session.call.CallState
import org.matrix.android.sdk.api.session.call.MxCall
import org.matrix.android.sdk.api.session.call.MxPeerConnectionState
import org.matrix.android.sdk.api.session.getRoomSummary
import org.matrix.android.sdk.api.session.room.model.call.supportCallTransfer
import org.matrix.android.sdk.api.util.MatrixItem

class ProgressiveCallViewModel @AssistedInject constructor(
        @Assisted initialState: ProgressiveCallViewState,
        val session: Session,
        val callManager: WebRtcCallManager,
        val proximityManager: CallProximityManager,
        private val dialPadLookup: DialPadLookup,
        private val directRoomHelper: DirectRoomHelper,
) : ProgressiveViewModel<ProgressiveCallViewState, ProgressiveCallViewActions, ProgressiveCallViewEvents>(initialState) {

    private var call: WebRtcCall? = null

    private var connectionTimeoutJob: Job? = null
    private var hasBeenConnectedOnce = false

    private val callListener = object : WebRtcCall.Listener {

        override fun onHoldUnhold() {
            setState {
                copy(
                        isLocalOnHold = call?.isLocalOnHold ?: false,
                        isRemoteOnHold = call?.isRemoteOnHold ?: false
                )
            }
        }

        override fun onCaptureStateChanged() {
            setState {
                copy(
                        isVideoCaptureInError = call?.videoCapturerIsInError ?: false,
                        isHD = call?.currentCaptureFormat() is CaptureFormat.HD
                )
            }
        }

        override fun onCameraChanged() {
            setState {
                copy(
                        canSwitchCamera = call?.canSwitchCamera() ?: false,
                        isFrontCamera = call?.currentCameraType() == CameraType.FRONT
                )
            }
        }

        override fun onTick(formattedDuration: String) {
            setState {
                copy(formattedDuration = formattedDuration)
            }
        }

        override fun assertedIdentityChanged() {
            setState {
                copy(callInfo = call?.extractCallInfo())
            }
        }

        override fun onStateUpdate(call: MxCall) {
            val callState = call.state
            if (callState is CallState.Connected && callState.iceConnectionState == MxPeerConnectionState.CONNECTED) {
                hasBeenConnectedOnce = true
                connectionTimeoutJob?.cancel()
                connectionTimeoutJob = null
            } else {
                // do we reset as long as it's moving?
                connectionTimeoutJob?.cancel()
                if (hasBeenConnectedOnce) {
                    connectionTimeoutJob = viewModelScope.launch {
                        delay(30_000)
                        try {
                            val turn = session.callSignalingService().getTurnServer()
                            _viewEvents.post(ProgressiveCallViewEvents.ConnectionTimeout(turn))
                        } catch (failure: Throwable) {
                            _viewEvents.post(ProgressiveCallViewEvents.ConnectionTimeout(null))
                        }
                    }
                }
            }
            setState {
                copy(
                        callState = Success(callState),
                        canOpponentBeTransferred = call.capabilities.supportCallTransfer(),
                        transferee = computeTransfereeState(call)
                )
            }
        }
    }

    private fun computeTransfereeState(call: MxCall): ProgressiveCallViewState.TransfereeState {
        val transfereeCall = callManager.getTransfereeForCallId(call.callId) ?: return ProgressiveCallViewState.TransfereeState.NoTransferee
        val transfereeRoom = session.getRoomSummary(transfereeCall.nativeRoomId)
        return transfereeRoom?.displayName?.let {
            ProgressiveCallViewState.TransfereeState.KnownTransferee(it)
        } ?: ProgressiveCallViewState.TransfereeState.UnknownTransferee
    }

    private val callManagerListener = object : WebRtcCallManager.Listener {

        override fun onCallEnded(callId: String) {
            withState { state ->
                if (state.otherKnownCallInfo?.callId == callId) {
                    setState { copy(otherKnownCallInfo = null, isSharingScreen = false) }
                }
            }
            _viewEvents.post(ProgressiveCallViewEvents.StopScreenSharingService)
        }

        override fun onCurrentCallChange(call: WebRtcCall?) {
            if (call != null) {
                updateOtherKnownCall(call)
            }
        }

        override fun onAudioDevicesChange() = withState { state ->
            val currentSoundDevice = callManager.audioManager.selectedDevice ?: return@withState
            val webRtcCall = callManager.getCallById(state.callId)
            if (webRtcCall != null && shouldActivateProximitySensor(webRtcCall)) {
                proximityManager.start()
            } else {
                proximityManager.stop()
            }
            setState {
                copy(
                        availableDevices = callManager.audioManager.availableDevices,
                        device = currentSoundDevice
                )
            }
        }
    }

    private fun updateOtherKnownCall(currentCall: WebRtcCall) {
        val otherCall = getOtherKnownCall(currentCall)
        setState {
            if (otherCall == null) {
                copy(otherKnownCallInfo = null)
            } else {
                copy(otherKnownCallInfo = otherCall.extractCallInfo())
            }
        }
    }

    private fun getOtherKnownCall(currentCall: WebRtcCall): WebRtcCall? {
        return callManager.getCalls().firstOrNull {
            it.callId != currentCall.callId && it.mxCall.state is CallState.Connected
        }
    }

    init {
        setupCallWithCurrentState()
    }

    private fun setupCallWithCurrentState() = withState { state ->
        call?.removeListener(callListener)
        val webRtcCall = callManager.getCallById(state.callId)
        if (webRtcCall == null) {
            setState {
                copy(callState = Fail(IllegalArgumentException("No call")))
            }
        } else {
            call = webRtcCall
            callManager.addListener(callManagerListener)
            webRtcCall.addListener(callListener)
            val currentSoundDevice = callManager.audioManager.selectedDevice
            if (shouldActivateProximitySensor(webRtcCall)) {
                proximityManager.start()
            }
            setState {
                copy(
                        isAudioMuted = webRtcCall.micMuted,
                        isVideoEnabled = !webRtcCall.videoMuted,
                        isVideoCall = webRtcCall.mxCall.isVideoCall,
                        callState = Success(webRtcCall.mxCall.state),
                        callInfo = webRtcCall.extractCallInfo(),
                        device = currentSoundDevice ?: CallAudioManager.Device.Phone,
                        isLocalOnHold = webRtcCall.isLocalOnHold,
                        isRemoteOnHold = webRtcCall.isRemoteOnHold,
                        availableDevices = callManager.audioManager.availableDevices,
                        isFrontCamera = webRtcCall.currentCameraType() == CameraType.FRONT,
                        canSwitchCamera = webRtcCall.canSwitchCamera(),
                        formattedDuration = webRtcCall.formattedDuration(),
                        isHD = webRtcCall.mxCall.isVideoCall && webRtcCall.currentCaptureFormat() is CaptureFormat.HD,
                        canOpponentBeTransferred = webRtcCall.mxCall.capabilities.supportCallTransfer(),
                        transferee = computeTransfereeState(webRtcCall.mxCall),
                        isSharingScreen = webRtcCall.isSharingScreen()
                )
            }
            updateOtherKnownCall(webRtcCall)
        }
    }

    private fun shouldActivateProximitySensor(webRtcCall: WebRtcCall): Boolean {
        return callManager.audioManager.selectedDevice == CallAudioManager.Device.Phone && !webRtcCall.isSharingScreen()
    }

    private fun WebRtcCall.extractCallInfo(): ProgressiveCallViewState.CallInfo {
        val assertedIdentity = this.remoteAssertedIdentity
        val matrixItem = if (assertedIdentity != null) {
            val userId = if (MatrixPatterns.isUserId(assertedIdentity.id)) {
                assertedIdentity.id!!
            } else {
                // Need an id starting with @
                "@${assertedIdentity.displayName}"
            }
            MatrixItem.UserItem(userId, assertedIdentity.displayName, assertedIdentity.avatarUrl)
        } else {
            getOpponentAsMatrixItem(session)
        }
        return ProgressiveCallViewState.CallInfo(callId, matrixItem)
    }

    override fun onCleared() {
        callManager.removeListener(callManagerListener)
        call?.removeListener(callListener)
        call = null
        proximityManager.stop()
        super.onCleared()
    }

    override fun handle(action: ProgressiveCallViewActions) = withState { state ->
        when (action) {
            ProgressiveCallViewActions.EndCall -> {
                call?.endCall()
                _viewEvents.post(ProgressiveCallViewEvents.StopScreenSharingService)
            }
            ProgressiveCallViewActions.AcceptCall -> {
                setState {
                    copy(callState = Loading())
                }
                call?.acceptIncomingCall()
            }
            ProgressiveCallViewActions.DeclineCall -> {
                setState {
                    copy(callState = Loading())
                }
                call?.endCall()
            }
            ProgressiveCallViewActions.ToggleMute -> {
                val muted = state.isAudioMuted
                call?.muteCall(!muted)
                setState {
                    copy(isAudioMuted = !muted)
                }
            }
            ProgressiveCallViewActions.ToggleVideo -> {
                if (state.isVideoCall) {
                    val videoEnabled = state.isVideoEnabled
                    call?.enableVideo(!videoEnabled)
                    setState {
                        copy(isVideoEnabled = !videoEnabled)
                    }
                }
                Unit
            }
            ProgressiveCallViewActions.ToggleHoldResume -> {
                val isRemoteOnHold = state.isRemoteOnHold
                call?.updateRemoteOnHold(!isRemoteOnHold)
            }
            is ProgressiveCallViewActions.ChangeAudioDevice -> {
                callManager.audioManager.setAudioDevice(action.device)
            }
            ProgressiveCallViewActions.SwitchSoundDevice -> {
                _viewEvents.post(
                        ProgressiveCallViewEvents.ShowSoundDeviceChooser(state.availableDevices, state.device)
                )
            }
            ProgressiveCallViewActions.HeadSetButtonPressed -> {
                if (state.callState.invoke() is CallState.LocalRinging) {
                    // accept call
                    call?.acceptIncomingCall()
                }
                if (state.callState.invoke() is CallState.Connected) {
                    // end call?
                    call?.endCall()
                }
                Unit
            }
            ProgressiveCallViewActions.ToggleCamera -> {
                call?.switchCamera()
            }
            ProgressiveCallViewActions.ToggleHDSD -> {
                if (!state.isVideoCall) return@withState
                call?.setCaptureFormat(if (state.isHD) CaptureFormat.SD else CaptureFormat.HD)
            }
            ProgressiveCallViewActions.OpenDialPad -> {
                _viewEvents.post(ProgressiveCallViewEvents.ShowDialPad)
            }
            is ProgressiveCallViewActions.SendDtmfDigit -> {
                call?.sendDtmfDigit(action.digit)
            }
            ProgressiveCallViewActions.InitiateCallTransfer -> {
                call?.updateRemoteOnHold(true)
                _viewEvents.post(
                        ProgressiveCallViewEvents.ShowCallTransferScreen
                )
            }
            ProgressiveCallViewActions.CallTransferSelectionCancelled -> {
                call?.updateRemoteOnHold(false)
            }
            is ProgressiveCallViewActions.CallTransferSelectionResult -> {
                handleCallTransferSelectionResult(action.callTransferResult)
            }
            ProgressiveCallViewActions.TransferCall -> {
                handleCallTransfer()
            }
            is ProgressiveCallViewActions.SwitchCall -> {
                setState { ProgressiveCallViewState(action.callArgs) }
                setupCallWithCurrentState()
            }
            is ProgressiveCallViewActions.ToggleScreenSharing -> {
                handleToggleScreenSharing(state.isSharingScreen)
            }
            is ProgressiveCallViewActions.StartScreenSharing -> {
                call?.startSharingScreen(action.videoCapturer)
                proximityManager.stop()
                setState {
                    copy(isSharingScreen = true)
                }
            }
        }
    }

    private fun handleToggleScreenSharing(isSharingScreen: Boolean) {
        if (isSharingScreen) {
            call?.stopSharingScreen()
            setState {
                copy(isSharingScreen = false)
            }
            _viewEvents.post(
                    ProgressiveCallViewEvents.StopScreenSharingService
            )
            if (callManager.audioManager.selectedDevice == CallAudioManager.Device.Phone) {
                proximityManager.start()
            }
        } else {
            _viewEvents.post(
                    ProgressiveCallViewEvents.ShowScreenSharingPermissionDialog
            )
        }
    }

    private fun handleCallTransfer() {
        viewModelScope.launch {
            val currentCall = call ?: return@launch
            val transfereeCall = callManager.getTransfereeForCallId(currentCall.callId) ?: return@launch
            currentCall.transferToCall(transfereeCall)
        }
    }

    private fun handleCallTransferSelectionResult(result: CallTransferResult) {
        when (result) {
            is CallTransferResult.ConnectWithUserId -> connectWithUserId(result)
            is CallTransferResult.ConnectWithPhoneNumber -> connectWithPhoneNumber(result)
        }
    }

    private fun connectWithUserId(result: CallTransferResult.ConnectWithUserId) {
        viewModelScope.launch {
            try {
                if (result.consultFirst) {
                    val dmRoomId = directRoomHelper.ensureDMExists(result.selectedUserId)
                    callManager.startOutgoingCall(
                            nativeRoomId = dmRoomId,
                            otherUserId = result.selectedUserId,
                            isVideoCall = call?.mxCall?.isVideoCall.orFalse(),
                            transferee = call
                    )
                } else {
                    call?.transferToUser(result.selectedUserId, null)
                }
            } catch (failure: Throwable) {
                _viewEvents.post(ProgressiveCallViewEvents.FailToTransfer)
            }
        }
    }

    private fun connectWithPhoneNumber(action: CallTransferResult.ConnectWithPhoneNumber) {
        viewModelScope.launch {
            try {
                val result = dialPadLookup.lookupPhoneNumber(action.phoneNumber)
                if (action.consultFirst) {
                    callManager.startOutgoingCall(
                            nativeRoomId = result.roomId,
                            otherUserId = result.userId,
                            isVideoCall = call?.mxCall?.isVideoCall.orFalse(),
                            transferee = call
                    )
                } else {
                    call?.transferToUser(result.userId, result.roomId)
                }
            } catch (failure: Throwable) {
                _viewEvents.post(ProgressiveCallViewEvents.FailToTransfer)
            }
        }
    }

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<ProgressiveCallViewModel, ProgressiveCallViewState> {
        override fun create(initialState: ProgressiveCallViewState): ProgressiveCallViewModel
    }

    companion object : MavericksViewModelFactory<ProgressiveCallViewModel, ProgressiveCallViewState> by hiltMavericksViewModelFactory()
}
