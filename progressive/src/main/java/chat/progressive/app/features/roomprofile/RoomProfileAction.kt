/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import org.matrix.android.sdk.api.session.room.notification.RoomNotificationState

sealed class RoomProfileAction : ProgressiveViewModelAction {
    object EnableEncryption : RoomProfileAction()
    object LeaveRoom : RoomProfileAction()
    data class ChangeRoomNotificationState(val notificationState: RoomNotificationState) : RoomProfileAction()
    object ShareRoomProfile : RoomProfileAction()
    object CreateShortcut : RoomProfileAction()
    object RestoreEncryptionState : RoomProfileAction()
    data class SetEncryptToVerifiedDeviceOnly(val enabled: Boolean) : RoomProfileAction()
    data class ReportRoom(val reason: String) : RoomProfileAction()
}
