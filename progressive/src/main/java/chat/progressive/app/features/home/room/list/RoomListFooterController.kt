/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list

import com.airbnb.epoxy.TypedEpoxyController
import chat.progressive.app.core.epoxy.helpFooterItem
import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.core.resources.UserPreferencesProvider
import chat.progressive.app.features.home.RoomListDisplayMode
import chat.progressive.app.features.home.room.filtered.FilteredRoomFooterItem
import chat.progressive.app.features.home.room.filtered.filteredRoomFooterItem
import chat.progressive.lib.strings.CommonStrings
import javax.inject.Inject

class RoomListFooterController @Inject constructor(
        private val stringProvider: StringProvider,
        private val userPreferencesProvider: UserPreferencesProvider
) : TypedEpoxyController<RoomListViewState>() {

    var listener: FilteredRoomFooterItem.Listener? = null

    override fun buildModels(data: RoomListViewState?) {
        val host = this
        when (data?.displayMode) {
            RoomListDisplayMode.FILTERED -> {
                filteredRoomFooterItem {
                    id("filter_footer")
                    listener(host.listener)
                    currentFilter(data.roomFilter)
                    inSpace(data.asyncSelectedSpace.invoke() != null)
                }
            }
            else -> {
                if (userPreferencesProvider.shouldShowLongClickOnRoomHelp()) {
                    helpFooterItem {
                        id("long_click_help")
                        text(host.stringProvider.getString(CommonStrings.help_long_click_on_room_for_more_options))
                    }
                }
            }
        }
    }
}
