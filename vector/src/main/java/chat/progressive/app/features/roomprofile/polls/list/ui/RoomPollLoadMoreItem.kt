/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.polls.list.ui

import android.widget.Button
import android.widget.ProgressBar
import androidx.core.view.isVisible
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick

@EpoxyModelClass
abstract class RoomPollLoadMoreItem : ProgressiveEpoxyModel<RoomPollLoadMoreItem.Holder>(R.layout.item_poll_load_more) {

    @EpoxyAttribute
    var loadingMore: Boolean = false

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var clickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.loadMoreButton.isEnabled = loadingMore.not()
        holder.loadMoreButton.onClick(clickListener)
        holder.loadMoreProgressBar.isVisible = loadingMore
    }

    class Holder : ProgressiveEpoxyHolder() {
        val loadMoreButton by bind<Button>(R.id.roomPollsLoadMore)
        val loadMoreProgressBar by bind<ProgressBar>(R.id.roomPollsLoadMoreProgress)
    }
}
