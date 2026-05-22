/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package im.vector.app.core.resources

import im.vector.app.features.settings.ProgressiveBasePreferences
import javax.inject.Inject

class UserPreferencesProvider @Inject constructor(private val progressivePreferences: ProgressiveBasePreferences) {

    fun shouldShowHiddenEvents(): Boolean {
        return progressivePreferences.shouldShowHiddenEvents()
    }

    fun shouldShowReadReceipts(): Boolean {
        return progressivePreferences.showReadReceipts()
    }

    fun shouldShowRedactedMessages(): Boolean {
        return progressivePreferences.showRedactedMessages()
    }

    fun shouldShowLongClickOnRoomHelp(): Boolean {
        return progressivePreferences.shouldShowLongClickOnRoomHelp()
    }

    fun neverShowLongClickOnRoomHelpAgain() {
        progressivePreferences.neverShowLongClickOnRoomHelpAgain()
    }

    fun shouldShowJoinLeaves(): Boolean {
        return progressivePreferences.showJoinLeaveMessages()
    }

    fun shouldShowAvatarDisplayNameChanges(): Boolean {
        return progressivePreferences.showAvatarDisplayNameChangeMessages()
    }

    fun areThreadMessagesEnabled(): Boolean {
        return progressivePreferences.areThreadMessagesEnabled()
    }

    fun showLiveSenderInfo(): Boolean {
        return progressivePreferences.showLiveSenderInfo()
    }

    fun autoplayAnimatedImages(): Boolean {
        return progressivePreferences.autoplayAnimatedImages()
    }
}
