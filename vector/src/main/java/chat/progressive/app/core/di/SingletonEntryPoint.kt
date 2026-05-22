/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.di

import dagger.hilt.EntryPoint
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import chat.progressive.app.core.dialogs.UnrecognizedCertificateDialog
import chat.progressive.app.core.error.ErrorFormatter
import chat.progressive.app.features.analytics.AnalyticsTracker
import chat.progressive.app.features.call.webrtc.WebRtcCallManager
import chat.progressive.app.features.home.AvatarRenderer
import chat.progressive.app.features.navigation.Navigator
import chat.progressive.app.features.pin.PinLocker
import chat.progressive.app.features.rageshake.BugReporter
import chat.progressive.app.features.session.SessionListener
import chat.progressive.app.features.settings.ProgressiveBasePreferences
import chat.progressive.app.features.ui.UiStateRepository
import chat.progressive.lib.core.utils.timer.Clock
import kotlinx.coroutines.CoroutineScope

@InstallIn(SingletonComponent::class)
@EntryPoint
interface SingletonEntryPoint {

    fun sessionListener(): SessionListener

    fun avatarRenderer(): AvatarRenderer

    fun activeSessionHolder(): ActiveSessionHolder

    fun unrecognizedCertificateDialog(): UnrecognizedCertificateDialog

    fun navigator(): Navigator

    fun clock(): Clock

    fun errorFormatter(): ErrorFormatter

    fun bugReporter(): BugReporter

    fun progressivePreferences(): ProgressiveBasePreferences

    fun uiStateRepository(): UiStateRepository

    fun pinLocker(): PinLocker

    fun analyticsTracker(): AnalyticsTracker

    fun webRtcCallManager(): WebRtcCallManager

    fun appCoroutineScope(): CoroutineScope
}
