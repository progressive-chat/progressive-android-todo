/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list.home.header

import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.features.home.room.list.UnreadCounterBadgeView

@EpoxyModelClass
abstract class InviteCounterItem : ProgressiveEpoxyModel<InviteCounterItem.Holder>(R.layout.item_invites_count) {

    @EpoxyAttribute var invitesCount: Int = 0
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var listener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.view.setOnClickListener(listener)
        holder.unreadCounterBadgeView.render(UnreadCounterBadgeView.State.Count(invitesCount, true))
    }

    class Holder : ProgressiveEpoxyHolder() {
        val unreadCounterBadgeView by bind<UnreadCounterBadgeView>(R.id.invites_count_badge)
    }
}
