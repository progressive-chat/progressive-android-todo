/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.crypto.keysbackup.settings

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class KeyBackupSettingsAction : ProgressiveViewModelAction {
    object Init : KeyBackupSettingsAction()
    object GetKeyBackupTrust : KeyBackupSettingsAction()
    object DeleteKeyBackup : KeyBackupSettingsAction()
    object SetUpKeyBackup : KeyBackupSettingsAction()
    data class StoreIn4SSuccess(val recoveryKey: String, val alias: String) : KeyBackupSettingsAction()
    object StoreIn4SReset : KeyBackupSettingsAction()
    object StoreIn4SFailure : KeyBackupSettingsAction()
}
