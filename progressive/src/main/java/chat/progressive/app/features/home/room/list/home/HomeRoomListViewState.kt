/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list.home

import com.airbnb.mvrx.MavericksState
import chat.progressive.app.core.platform.StateView
import chat.progressive.app.features.home.room.list.home.header.RoomsHeadersData

data class HomeRoomListViewState(
        val emptyState: StateView.State.Empty? = null,
        val headersData: RoomsHeadersData = RoomsHeadersData(),
) : MavericksState
