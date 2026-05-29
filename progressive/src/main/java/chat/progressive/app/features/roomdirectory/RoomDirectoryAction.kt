/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomdirectory

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import org.matrix.android.sdk.api.session.room.model.roomdirectory.PublicRoom

sealed class RoomDirectoryAction : ProgressiveViewModelAction {
    data class SetRoomDirectoryData(val roomDirectoryData: RoomDirectoryData) : RoomDirectoryAction()
    data class FilterWith(val filter: String) : RoomDirectoryAction()
    object LoadMore : RoomDirectoryAction()
    data class JoinRoom(val publicRoom: PublicRoom) : RoomDirectoryAction()
}
