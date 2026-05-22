/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list.home

import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.platform.StateView

@EpoxyModelClass
abstract class RoomListEmptyItem : ProgressiveEpoxyModel<RoomListEmptyItem.Holder>(R.layout.item_state_view) {

    @EpoxyAttribute
    lateinit var emptyData: StateView.State.Empty

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.stateView.state = emptyData
    }

    class Holder : ProgressiveEpoxyHolder() {
        val stateView by bind<StateView>(R.id.stateView)
    }
}
