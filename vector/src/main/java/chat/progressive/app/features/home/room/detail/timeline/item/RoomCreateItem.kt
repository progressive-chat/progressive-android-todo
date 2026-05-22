/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.timeline.item

import android.widget.TextView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.lib.core.utils.epoxy.charsequence.EpoxyCharSequence
import me.saket.bettermovementmethod.BetterLinkMovementMethod

@EpoxyModelClass
abstract class RoomCreateItem : ProgressiveEpoxyModel<RoomCreateItem.Holder>(R.layout.item_timeline_event_create) {

    @EpoxyAttribute lateinit var text: EpoxyCharSequence

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.description.movementMethod = BetterLinkMovementMethod.getInstance()
        holder.description.text = text.charSequence
    }

    class Holder : ProgressiveEpoxyHolder() {
        val description by bind<TextView>(R.id.roomCreateItemDescription)
    }
}
