/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.createdirect

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import chat.progressive.app.features.userdirectory.PendingSelection

sealed class CreateDirectRoomAction : ProgressiveViewModelAction {
    data class PrepareRoomWithSelectedUsers(
            val selections: Set<PendingSelection>
    ) : CreateDirectRoomAction()

    object CreateRoomAndInviteSelectedUsers : CreateDirectRoomAction()

    data class QrScannedAction(
            val result: String
    ) : CreateDirectRoomAction()
}
