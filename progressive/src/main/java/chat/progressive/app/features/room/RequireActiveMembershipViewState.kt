/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.room

import com.airbnb.mvrx.MavericksState
import chat.progressive.app.features.home.room.detail.arguments.TimelineArgs
import chat.progressive.app.features.roommemberprofile.RoomMemberProfileArgs
import chat.progressive.app.features.roomprofile.RoomProfileArgs

data class RequireActiveMembershipViewState(
        val roomId: String? = null
) : MavericksState {

    constructor(args: TimelineArgs) : this(roomId = args.roomId)

    constructor(args: RoomProfileArgs) : this(roomId = args.roomId)

    constructor(args: RoomMemberProfileArgs) : this(roomId = args.roomId)
}
