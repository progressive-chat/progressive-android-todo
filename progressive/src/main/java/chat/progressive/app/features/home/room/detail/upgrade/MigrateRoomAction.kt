/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.upgrade

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class MigrateRoomAction : ProgressiveViewModelAction {
    data class SetAutoInvite(val autoInvite: Boolean) : MigrateRoomAction()
    data class SetUpdateKnownParentSpace(val update: Boolean) : MigrateRoomAction()
    object UpgradeRoom : MigrateRoomAction()
}
