/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.call.webrtc

import android.content.Intent
import android.os.Binder
import android.os.IBinder
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.startForegroundCompat
import chat.progressive.app.core.services.ProgressiveService
import chat.progressive.app.features.notifications.NotificationUtils
import chat.progressive.lib.core.utils.timer.Clock
import javax.inject.Inject

@AndroidEntryPoint
class ScreenCaptureAndroidService : ProgressiveService() {

    @Inject lateinit var notificationUtils: NotificationUtils
    @Inject lateinit var clock: Clock
    private val binder = LocalBinder()

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        showStickyNotification()

        return START_STICKY
    }

    private fun showStickyNotification() {
        val notificationId = clock.epochMillis().toInt()
        val notification = notificationUtils.buildScreenSharingNotification()
        startForegroundCompat(notificationId, notification)
    }

    override fun onBind(intent: Intent?): IBinder {
        return binder
    }

    fun stopService() {
        stopSelf()
    }

    inner class LocalBinder : Binder() {
        fun getService(): ScreenCaptureAndroidService = this@ScreenCaptureAndroidService
    }
}
