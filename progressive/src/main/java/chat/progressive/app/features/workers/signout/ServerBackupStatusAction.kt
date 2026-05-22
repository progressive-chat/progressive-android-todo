/*
 * Copyright 2022-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.workers.signout

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed interface ServerBackupStatusAction : ProgressiveViewModelAction {
    data class OnRecoverDoneForVersion(val version: String) : ServerBackupStatusAction
    object OnBannerDisplayed : ServerBackupStatusAction
    object OnBannerClosed : ServerBackupStatusAction
}
