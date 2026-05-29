/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.polls.detail.ui

import android.widget.Button
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick

@EpoxyModelClass
abstract class RoomPollGoToTimelineItem : ProgressiveEpoxyModel<RoomPollGoToTimelineItem.Holder>(R.layout.item_poll_go_to_timeline) {

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var clickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.goToTimelineButton.onClick(clickListener)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val goToTimelineButton by bind<Button>(R.id.roomPollGoToTimeline)
    }
}
