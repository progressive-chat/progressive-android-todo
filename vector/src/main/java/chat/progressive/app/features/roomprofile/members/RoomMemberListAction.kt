/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.members

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class RoomMemberListAction : ProgressiveViewModelAction {
    data class RevokeThreePidInvite(val stateKey: String) : RoomMemberListAction()
    data class FilterMemberList(val searchTerm: String) : RoomMemberListAction()
}
