/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.composer.voice

import android.annotation.SuppressLint
import android.content.res.Resources
import android.text.format.DateUtils
import android.view.MotionEvent
import android.view.View
import android.view.ViewGroup
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.view.doOnLayout
import androidx.core.view.isInvisible
import androidx.core.view.isVisible
import androidx.core.view.updateLayoutParams
import chat.progressive.app.R
import chat.progressive.app.core.extensions.setAttributeBackground
import chat.progressive.app.core.extensions.setAttributeTintedBackground
import chat.progressive.app.core.extensions.setAttributeTintedImageResource
import chat.progressive.app.core.utils.DimensionConverter
import chat.progressive.app.databinding.ViewVoiceMessageRecorderBinding
import chat.progressive.app.features.home.room.detail.composer.voice.VoiceMessageRecorderView.DraggingState
import chat.progressive.app.features.home.room.detail.composer.voice.VoiceMessageRecorderView.RecordingUiState
import chat.progressive.app.features.home.room.detail.timeline.helper.AudioMessagePlaybackTracker
import chat.progressive.app.features.themes.ThemeUtils
import chat.progressive.app.features.voice.AudioWaveformView
import chat.progressive.lib.strings.CommonStrings

class VoiceMessageViews(
        private val resources: Resources,
        private val views: ViewVoiceMessageRecorderBinding,
        private val dimensionConverter: DimensionConverter,
) {
    var isVoiceAgentEnabled: Boolean = false
    var voiceButtonPreset: String = "vertical_split"

    // Tracks which mic button was used to start recording (null = room, non-null = agent)
    private var isAgentRecording: Boolean = false

    private val distanceToLock = dimensionConverter.dpToPx(48).toFloat()
    private val distanceToCancel = dimensionConverter.dpToPx(120).toFloat()
    private val rtlXMultiplier = resources.getInteger(chat.progressive.lib.ui.styles.R.integer.rtl_x_multiplier)

    fun start(actions: Actions) {
        views.voiceMessageSendButton.setOnClickListener {
            views.voiceMessageSendButton.isVisible = false
            actions.onSendVoiceMessage()
        }

        views.voiceMessageSendToAgentButton.setOnClickListener {
            views.voiceMessageSendToAgentButton.isVisible = false
            actions.onSendVoiceToAgent()
        }

        views.voiceMessageDeletePlayback.setOnClickListener {
            views.voiceMessageSendButton.isVisible = false
            actions.onDeleteVoiceMessage()
        }

        views.voicePlaybackWaveform.setOnTouchListener { view, motionEvent ->
            when (motionEvent.action) {
                MotionEvent.ACTION_DOWN -> {
                    actions.onWaveformClicked()
                }
                MotionEvent.ACTION_UP -> {
                    val percentage = getTouchedPositionPercentage(motionEvent, view)
                    actions.onVoiceWaveformTouchedUp(percentage)
                }
                MotionEvent.ACTION_MOVE -> {
                    val percentage = getTouchedPositionPercentage(motionEvent, view)
                    actions.onVoiceWaveformMoved(percentage)
                }
            }
            true
        }

        views.voicePlaybackControlButton.setOnClickListener {
            actions.onVoicePlaybackButtonClicked()
        }
        observeMicButtons(actions)
        applyPresetLayout()
    }

    private fun applyPresetLayout() {
        if (!isVoiceAgentEnabled) {
            views.voiceMessageMicAgentButton.isVisible = false
            // Reset room mic to default position
            views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(16))
            }
            return
        }

        views.voiceMessageMicAgentButton.isVisible = true

        when (voiceButtonPreset) {
            "vertical_split" -> {
                // Room mic (bottom), Agent mic (top) — stacked vertically
                views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(6))
                }
                views.voiceMessageMicAgentButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(56))
                }
                // Make the agent button larger (top portion of split)
                views.voiceMessageMicAgentButton.scaleX = 1.3f
                views.voiceMessageMicAgentButton.scaleY = 1.3f
                views.voiceMessageMicButton.scaleX = 0.8f
                views.voiceMessageMicButton.scaleY = 0.8f
            }
            "horizontal_side" -> {
                // Room mic (left), Agent mic (right) — side by side
                views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(52), dimensionConverter.dpToPx(16))
                }
                views.voiceMessageMicAgentButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(16))
                }
                views.voiceMessageMicAgentButton.scaleX = 1.0f
                views.voiceMessageMicAgentButton.scaleY = 1.0f
                views.voiceMessageMicButton.scaleX = 1.0f
                views.voiceMessageMicButton.scaleY = 1.0f
            }
            "floating" -> {
                // Room mic stays in default position
                views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(16))
                }
                // Agent mic floats above (higher up)
                views.voiceMessageMicAgentButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                    setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(120))
                }
                views.voiceMessageMicAgentButton.scaleX = 1.0f
                views.voiceMessageMicAgentButton.scaleY = 1.0f
                views.voiceMessageMicButton.scaleX = 1.0f
                views.voiceMessageMicButton.scaleY = 1.0f
            }
        }
    }

    private fun getTouchedPositionPercentage(motionEvent: MotionEvent, view: View) = (motionEvent.x / view.width).coerceIn(0f, 1f)

    @SuppressLint("ClickableViewAccessibility")
    private fun observeMicButtons(actions: Actions) {
        val draggableStateProcessor = DraggableStateProcessor(resources, dimensionConverter)

        // Room mic button
        views.voiceMessageMicButton.setOnTouchListener { _, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isAgentRecording = false
                    draggableStateProcessor.initialize(event)
                    actions.onRequestRecording()
                    true
                }
                MotionEvent.ACTION_UP -> {
                    actions.onMicButtonReleased()
                    true
                }
                MotionEvent.ACTION_MOVE -> {
                    actions.onMicButtonDrag { currentState -> draggableStateProcessor.process(event, currentState) }
                    true
                }
                else -> false
            }
        }

        // AI agent mic button — only active when voice agent is enabled
        views.voiceMessageMicAgentButton.setOnTouchListener { _, event ->
            if (!isVoiceAgentEnabled) return@setOnTouchListener false
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    isAgentRecording = true
                    draggableStateProcessor.initialize(event)
                    actions.onRequestRecording()
                    true
                }
                MotionEvent.ACTION_UP -> {
                    actions.onMicButtonReleased()
                    true
                }
                MotionEvent.ACTION_MOVE -> {
                    actions.onMicButtonDrag { currentState -> draggableStateProcessor.process(event, currentState) }
                    true
                }
                else -> false
            }
        }
    }

    fun isAgentRecording(): Boolean = isAgentRecording

    fun resetRecordingTarget() {
        isAgentRecording = false
    }

    fun renderStarted(distanceX: Float) {
        val translationAmount = distanceX.coerceAtMost(distanceToCancel)
        views.voiceMessageMicButton.translationX = -translationAmount * rtlXMultiplier
        views.voiceMessageSlideToCancel.translationX = -translationAmount / 2 * rtlXMultiplier
    }

    fun renderLocked() {
        views.voiceMessageLockImage.setImageResource(R.drawable.ic_voice_message_locked)
    }

    fun renderLocking(distanceY: Float) {
        views.voiceMessageLockImage.setAttributeTintedImageResource(R.drawable.ic_voice_message_locked, com.google.android.material.R.attr.colorPrimary)
        val translationAmount = -distanceY.coerceIn(0F, distanceToLock)
        views.voiceMessageMicButton.translationY = translationAmount
        views.voiceMessageLockArrow.translationY = translationAmount
        views.voiceMessageLockArrow.alpha = 1 - (-translationAmount / distanceToLock)
        // Reset X translations
        views.voiceMessageMicButton.translationX = 0F
        views.voiceMessageSlideToCancel.translationX = 0F
    }

    fun renderCancelling(distanceX: Float) {
        val translationAmount = distanceX.coerceAtMost(distanceToCancel)
        views.voiceMessageMicButton.translationX = -translationAmount * rtlXMultiplier
        views.voiceMessageSlideToCancel.translationX = -translationAmount / 2 * rtlXMultiplier
        val reducedAlpha = (1 - translationAmount / distanceToCancel / 1.5).toFloat()
        views.voiceMessageSlideToCancel.alpha = reducedAlpha
        views.voiceMessageTimerIndicator.alpha = reducedAlpha
        views.voiceMessageTimer.alpha = reducedAlpha
        views.voiceMessageLockBackground.isVisible = false
        views.voiceMessageLockImage.isVisible = false
        views.voiceMessageLockArrow.isVisible = false
        views.voiceMessageSlideToCancelDivider.isVisible = true
        // Reset Y translations
        views.voiceMessageMicButton.translationY = 0F
        views.voiceMessageLockArrow.translationY = 0F
    }

    fun showRecordingViews() {
        views.voiceMessageBackgroundView.isVisible = true
        // Highlight the active mic button
        if (isAgentRecording) {
            views.voiceMessageMicAgentButton.setImageResource(R.drawable.ic_composer_rich_mic_pressed)
            views.voiceMessageMicAgentButton.setAttributeTintedBackground(R.drawable.circle_with_halo, com.google.android.material.R.attr.colorPrimary)
            views.voiceMessageMicAgentButton.animate().scaleX(1.8f).scaleY(1.8f).setDuration(300).start()
            views.voiceMessageMicButton.isVisible = false
        } else {
            views.voiceMessageMicButton.setImageResource(R.drawable.ic_composer_rich_mic_pressed)
            views.voiceMessageMicButton.setAttributeTintedBackground(R.drawable.circle_with_halo, com.google.android.material.R.attr.colorPrimary)
            views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
                setMargins(0, 0, 0, 0)
            }
            views.voiceMessageMicButton.animate().scaleX(1.5f).scaleY(1.5f).setDuration(300).start()
            views.voiceMessageMicAgentButton.isVisible = false
        }

        views.voiceMessageLockBackground.isVisible = true
        views.voiceMessageLockBackground.animate().setDuration(300).translationY(-dimensionConverter.dpToPx(180).toFloat()).start()
        views.voiceMessageLockImage.isVisible = true
        views.voiceMessageLockImage.setImageResource(R.drawable.ic_voice_message_unlocked)
        views.voiceMessageLockImage.animate().setDuration(500).translationY(-dimensionConverter.dpToPx(180).toFloat()).start()
        views.voiceMessageLockArrow.isVisible = true
        views.voiceMessageLockArrow.alpha = 1f
        views.voiceMessageSlideToCancel.isVisible = true
        views.voiceMessageTimerIndicator.isVisible = true
        views.voiceMessageTimer.isVisible = true
        views.voiceMessageSlideToCancel.alpha = 1f
        views.voiceMessageTimerIndicator.alpha = 1f
        views.voiceMessageTimer.alpha = 1f
        views.voiceMessageSendButton.isVisible = false
    }

    fun hideRecordingViews(recordingState: RecordingUiState) {
        views.voiceMessageBackgroundView.isVisible = false
        if (recordingState !is RecordingUiState.Locked) {
            views.voiceMessageLockImage.isVisible = false
            views.voiceMessageLockImage.animate().translationY(0f).start()
            views.voiceMessageLockBackground.isVisible = false
            views.voiceMessageLockBackground.animate().translationY(0f).start()
        } else {
            animateLockImageWithBackground()
        }
        views.voiceMessageSlideToCancelDivider.isVisible = false
        views.voiceMessageLockArrow.isVisible = false
        views.voiceMessageLockArrow.animate().translationY(0f).start()
        views.voiceMessageSlideToCancel.isVisible = false
        views.voiceMessageSlideToCancel.animate().translationX(0f).translationY(0f).start()
        views.voiceMessagePlaybackLayout.isVisible = false
        views.voiceMessageTimerIndicator.isVisible = false
        views.voiceMessageTimer.isVisible = false
        views.voiceMessageMicAgentButton.isVisible = false

        if (recordingState !is RecordingUiState.Locked) {
            views.voiceMessageMicButton
                    .animate()
                    .scaleX(1f)
                    .scaleY(1f)
                    .translationX(0f)
                    .translationY(0f)
                    .setDuration(150)
                    .withEndAction {
                        resetMicButtonUi()
                    }
                    .start()
        } else {
            views.voiceMessageTimerIndicator.isVisible = false
            views.voiceMessageTimer.isVisible = false
            views.voiceMessageMicButton.apply {
                scaleX = 1f
                scaleY = 1f
                translationX = 0f
                translationY = 0f
            }
        }

        if (recordingState == RecordingUiState.Idle) {
            hideToast()
        }
    }

    fun animateLockImageWithBackground() {
        views.voiceMessageLockBackground.updateLayoutParams {
            height = dimensionConverter.dpToPx(78)
        }
        views.voiceMessageLockBackground.apply {
            animate()
                    .scaleX(0f)
                    .scaleY(0f)
                    .setDuration(400L)
                    .withEndAction {
                        updateLayoutParams {
                            height = dimensionConverter.dpToPx(180)
                        }
                        isVisible = false
                        scaleX = 1f
                        scaleY = 1f
                        animate().translationY(0f).start()
                    }
                    .start()
        }

        // Lock image animation
        views.voiceMessageMicButton.isInvisible = true
        views.voiceMessageLockImage.apply {
            isVisible = true
            animate()
                    .scaleX(0f)
                    .scaleY(0f)
                    .setDuration(400L)
                    .withEndAction {
                        isVisible = false
                        scaleX = 1f
                        scaleY = 1f
                        translationY = 0f
                        resetMicButtonUi()
                    }
                    .start()
        }
    }

    fun resetMicButtonUi() {
        views.voiceMessageMicButton.isVisible = true
        views.voiceMessageMicButton.setImageResource(R.drawable.ic_microphone)
        views.voiceMessageMicButton.setAttributeBackground(android.R.attr.selectableItemBackgroundBorderless)
        views.voiceMessageMicButton.updateLayoutParams<ViewGroup.MarginLayoutParams> {
            if (rtlXMultiplier == -1) {
                setMargins(dimensionConverter.dpToPx(12), 0, 0, dimensionConverter.dpToPx(12))
            } else {
                setMargins(0, 0, dimensionConverter.dpToPx(12), dimensionConverter.dpToPx(12))
            }
        }
        // Restore agent button
        if (isVoiceAgentEnabled) {
            applyPresetLayout()
        }
        resetRecordingTarget()
    }

    fun hideToast() {
        views.voiceMessageToast.isVisible = false
    }

    fun showDraftViews() {
        hideRecordingViews(RecordingUiState.Idle)
        views.voiceMessageBackgroundView.isVisible = true
        views.voiceMessageMicButton.isVisible = false
        views.voiceMessageMicAgentButton.isVisible = false
        views.voiceMessageSendButton.isVisible = true
        views.voiceMessageSendToAgentButton.isVisible = isVoiceAgentEnabled
        views.voiceMessagePlaybackLayout.isVisible = true
        views.voiceMessagePlaybackTimerIndicator.isVisible = false
        views.voicePlaybackControlButton.isVisible = true
        views.voicePlaybackWaveform.importantForAccessibility = View.IMPORTANT_FOR_ACCESSIBILITY_NO
    }

    fun showRecordingLockedViews(recordingState: RecordingUiState) {
        hideRecordingViews(recordingState)
        views.voiceMessageBackgroundView.isVisible = true
        views.voiceMessagePlaybackLayout.isVisible = true
        views.voiceMessagePlaybackTimerIndicator.isVisible = true
        views.voicePlaybackControlButton.isVisible = false
        views.voiceMessageSendButton.isVisible = true
        views.voiceMessageSendToAgentButton.isVisible = isVoiceAgentEnabled
        views.voicePlaybackWaveform.importantForAccessibility = View.IMPORTANT_FOR_ACCESSIBILITY_YES
        renderToast(resources.getString(CommonStrings.voice_message_tap_to_stop_toast))
    }

    fun initViews() {
        hideRecordingViews(RecordingUiState.Idle)
        views.voiceMessageMicButton.isVisible = true
        views.voiceMessageSendButton.isVisible = false
        views.voicePlaybackWaveform.post { views.voicePlaybackWaveform.clear() }
    }

    fun renderPlaying(state: AudioMessagePlaybackTracker.Listener.State.Playing) {
        views.voicePlaybackControlButton.setImageResource(R.drawable.ic_play_pause_pause)
        views.voicePlaybackControlButton.contentDescription = resources.getString(CommonStrings.a11y_pause_voice_message)
        val formattedTimerText = DateUtils.formatElapsedTime((state.playbackTime / 1000).toLong())
        views.voicePlaybackTime.text = formattedTimerText
        val waveformColorIdle = ThemeUtils.getColor(views.voicePlaybackWaveform.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_quaternary)
        val waveformColorPlayed = ThemeUtils.getColor(views.voicePlaybackWaveform.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_secondary)
        views.voicePlaybackWaveform.updateColors(state.percentage, waveformColorPlayed, waveformColorIdle)
    }

    fun renderIdle() {
        views.voicePlaybackControlButton.setImageResource(R.drawable.ic_play_pause_play)
        views.voicePlaybackControlButton.contentDescription = resources.getString(CommonStrings.a11y_play_voice_message)
        views.voicePlaybackWaveform.summarize()
    }

    fun renderToast(message: String) {
        views.voiceMessageToast.removeCallbacks(hideToastRunnable)
        views.voiceMessageToast.text = message
        views.voiceMessageToast.isVisible = true
        views.voiceMessageToast.postDelayed(hideToastRunnable, 2_000)
    }

    private val hideToastRunnable = Runnable {
        views.voiceMessageToast.isVisible = false
    }

    fun renderRecordingTimer(isLocked: Boolean, recordingTimeMillis: Long) {
        val formattedTimerText = DateUtils.formatElapsedTime(recordingTimeMillis)
        if (isLocked) {
            views.voicePlaybackTime.apply {
                post {
                    text = formattedTimerText
                }
            }
        } else {
            views.voiceMessageTimer.post {
                views.voiceMessageTimer.text = formattedTimerText
            }
        }
    }

    fun renderRecordingWaveform(amplitudeList: List<Int>) {
        views.voicePlaybackWaveform.doOnLayout { waveFormView ->
            val waveformColor = ThemeUtils.getColor(waveFormView.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_quaternary)
            amplitudeList.forEach {
                (waveFormView as AudioWaveformView).add(AudioWaveformView.FFT(it.toFloat(), waveformColor))
            }
        }
    }

    fun renderVisibilityChanged(parentChanged: Boolean, visibility: Int) {
        if (parentChanged && visibility == ConstraintLayout.VISIBLE) {
            views.voiceMessageMicButton.contentDescription = resources.getString(CommonStrings.a11y_start_voice_message)
        } else {
            views.voiceMessageMicButton.contentDescription = ""
        }
    }

    interface Actions {
        fun onRequestRecording()
        fun onMicButtonReleased()
        fun onMicButtonDrag(nextDragStateCreator: (DraggingState) -> DraggingState)
        fun onSendVoiceMessage()
        fun onSendVoiceToAgent()
        fun onDeleteVoiceMessage()
        fun onWaveformClicked()
        fun onVoicePlaybackButtonClicked()
        fun onVoiceWaveformTouchedUp(percentage: Float)
        fun onVoiceWaveformMoved(percentage: Float)
    }
}
