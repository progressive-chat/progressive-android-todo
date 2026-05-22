/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.session

import android.content.Context
import dagger.hilt.android.qualifiers.ApplicationContext
import chat.progressive.app.core.extensions.startSyncing
import chat.progressive.app.core.notification.NotificationsSettingUpdater
import chat.progressive.app.core.notification.PushRulesUpdater
import chat.progressive.app.core.session.clientinfo.UpdateMatrixClientInfoUseCase
import chat.progressive.app.features.call.webrtc.WebRtcCallManager
import chat.progressive.app.features.session.coroutineScope
import chat.progressive.app.features.settings.ProgressiveBasePreferences
import chat.progressive.app.features.settings.devices.v2.notification.UpdateNotificationSettingsAccountDataUseCase
import kotlinx.coroutines.launch
import org.matrix.android.sdk.api.session.Session
import timber.log.Timber
import javax.inject.Inject

class ConfigureAndStartSessionUseCase @Inject constructor(
        @ApplicationContext private val context: Context,
        private val webRtcCallManager: WebRtcCallManager,
        private val updateMatrixClientInfoUseCase: UpdateMatrixClientInfoUseCase,
        private val progressivePreferences: ProgressiveBasePreferences,
        private val notificationsSettingUpdater: NotificationsSettingUpdater,
        private val updateNotificationSettingsAccountDataUseCase: UpdateNotificationSettingsAccountDataUseCase,
        private val pushRulesUpdater: PushRulesUpdater,
) {

    fun execute(session: Session, startSyncing: Boolean = true) {
        Timber.i("Configure and start session for ${session.myUserId}. startSyncing: $startSyncing")
        session.open()
        if (startSyncing) {
            session.startSyncing(context)
        }
        session.pushersService().refreshPushers()
        webRtcCallManager.checkForProtocolsSupportIfNeeded()
        updateMatrixClientInfoIfNeeded(session)
        createNotificationSettingsAccountDataIfNeeded(session)
        notificationsSettingUpdater.onSessionStarted(session)
        pushRulesUpdater.onSessionStarted(session)
    }

    private fun updateMatrixClientInfoIfNeeded(session: Session) {
        session.coroutineScope.launch {
            if (progressivePreferences.isClientInfoRecordingEnabled()) {
                updateMatrixClientInfoUseCase.execute(session)
            }
        }
    }

    private fun createNotificationSettingsAccountDataIfNeeded(session: Session) {
        session.coroutineScope.launch {
            updateNotificationSettingsAccountDataUseCase.execute(session)
        }
    }
}
