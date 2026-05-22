/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.invite

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import chat.progressive.app.features.userdirectory.PendingSelection

sealed class InviteUsersToRoomAction : ProgressiveViewModelAction {
    data class InviteSelectedUsers(val selections: Set<PendingSelection>) : InviteUsersToRoomAction()
}
