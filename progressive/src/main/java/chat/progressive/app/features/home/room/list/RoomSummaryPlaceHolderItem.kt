/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list

import android.widget.TextView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel

@EpoxyModelClass
abstract class RoomSummaryPlaceHolderItem : ProgressiveEpoxyModel<RoomSummaryPlaceHolderItem.Holder>(R.layout.item_room_placeholder) {

    @EpoxyAttribute
    var useSingleLineForLastEvent: Boolean = false

    override fun bind(holder: Holder) {
        super.bind(holder)
        if (useSingleLineForLastEvent) {
            holder.subtitleView.setLines(1)
        }
    }

    class Holder : ProgressiveEpoxyHolder() {
        val subtitleView by bind<TextView>(R.id.subtitleView)
    }
}
