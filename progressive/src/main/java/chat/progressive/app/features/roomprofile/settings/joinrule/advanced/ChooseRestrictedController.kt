/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.settings.joinrule.advanced

import com.airbnb.epoxy.TypedEpoxyController
import com.airbnb.mvrx.Fail
import com.airbnb.mvrx.Loading
import com.airbnb.mvrx.Success
import com.airbnb.mvrx.Uninitialized
import chat.progressive.app.core.epoxy.loadingItem
import chat.progressive.app.core.epoxy.noResultItem
import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.core.ui.list.genericFooterItem
import chat.progressive.app.features.home.AvatarRenderer
import chat.progressive.app.features.spaces.manage.roomSelectionItem
import chat.progressive.lib.core.utils.epoxy.charsequence.toEpoxyCharSequence
import chat.progressive.lib.strings.CommonStrings
import org.matrix.android.sdk.api.util.MatrixItem
import javax.inject.Inject

class ChooseRestrictedController @Inject constructor(
        private val stringProvider: StringProvider,
        private val avatarRenderer: AvatarRenderer
) : TypedEpoxyController<RoomJoinRuleChooseRestrictedState>() {

    interface Listener {
        fun onItemSelected(matrixItem: MatrixItem)
    }

    var listener: Listener? = null

    override fun buildModels(data: RoomJoinRuleChooseRestrictedState?) {
        data ?: return
        val host = this

        if (data.filter.isNotEmpty()) {
            when (val results = data.filteredResults) {
                Uninitialized,
                is Fail -> return
                is Loading -> loadingItem { id("filter_load") }
                is Success -> {
                    if (results.invoke().isEmpty()) {
                        noResultItem {
                            id("empty")
                            text(host.stringProvider.getString(CommonStrings.no_result_placeholder))
                        }
                    } else {
                        results.invoke().forEach { matrixItem ->
                            roomSelectionItem {
                                id(matrixItem.id)
                                matrixItem(matrixItem)
                                avatarRenderer(host.avatarRenderer)
                                selected(data.updatedAllowList.firstOrNull { it.id == matrixItem.id } != null)
                                itemClickListener { host.listener?.onItemSelected(matrixItem) }
                            }
                        }
                    }
                }
            }
            return
        }

        // when no filters
        genericFooterItem {
            id("h1")
            text(host.stringProvider.getString(CommonStrings.space_you_know_that_contains_this_room).toEpoxyCharSequence())
            centered(false)
        }

        data.possibleSpaceCandidate.forEach { matrixItem ->
            roomSelectionItem {
                id(matrixItem.id)
                matrixItem(matrixItem)
                avatarRenderer(host.avatarRenderer)
                selected(data.updatedAllowList.firstOrNull { it.id == matrixItem.id } != null)
                itemClickListener { host.listener?.onItemSelected(matrixItem) }
            }
        }

        if (data.unknownRestricted.isNotEmpty()) {
            genericFooterItem {
                id("others")
                text(host.stringProvider.getString(CommonStrings.other_spaces_or_rooms_you_might_not_know).toEpoxyCharSequence())
                centered(false)
            }

            data.unknownRestricted.forEach { matrixItem ->
                roomSelectionItem {
                    id(matrixItem.id)
                    matrixItem(matrixItem)
                    avatarRenderer(host.avatarRenderer)
                    selected(data.updatedAllowList.firstOrNull { it.id == matrixItem.id } != null)
                    itemClickListener { host.listener?.onItemSelected(matrixItem) }
                }
            }
        }
    }
}
