/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.notifications

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import org.matrix.android.sdk.api.session.room.notification.RoomNotificationState

sealed class RoomNotificationSettingsAction : ProgressiveViewModelAction {
    data class SelectNotificationState(val notificationState: RoomNotificationState) : RoomNotificationSettingsAction()
}
