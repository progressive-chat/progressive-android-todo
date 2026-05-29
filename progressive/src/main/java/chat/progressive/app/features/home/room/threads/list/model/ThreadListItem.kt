/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.threads.list.model

import android.widget.ImageView
import android.widget.TextView
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.content.ContextCompat
import androidx.core.view.isVisible
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.clearDrawables
import chat.progressive.app.core.extensions.setLeftDrawable
import chat.progressive.app.core.utils.DimensionConverter
import chat.progressive.app.features.displayname.getBestName
import chat.progressive.app.features.home.AvatarRenderer
import chat.progressive.app.features.themes.ThemeUtils
import chat.progressive.lib.strings.CommonStrings
import org.matrix.android.sdk.api.session.threads.ThreadNotificationState
import org.matrix.android.sdk.api.util.MatrixItem

@EpoxyModelClass
abstract class ThreadListItem : ProgressiveEpoxyModel<ThreadListItem.Holder>(R.layout.item_thread) {

    @EpoxyAttribute lateinit var avatarRenderer: AvatarRenderer
    @EpoxyAttribute lateinit var matrixItem: MatrixItem
    @EpoxyAttribute lateinit var title: String
    @EpoxyAttribute lateinit var date: String
    @EpoxyAttribute lateinit var rootMessage: String
    @EpoxyAttribute lateinit var lastMessage: String
    @EpoxyAttribute var threadNotificationState: ThreadNotificationState = ThreadNotificationState.NO_NEW_MESSAGE
    @EpoxyAttribute lateinit var lastMessageCounter: String
    @EpoxyAttribute var rootMessageDeleted: Boolean = false
    @EpoxyAttribute var lastMessageMatrixItem: MatrixItem? = null
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var itemClickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.rootView.onClick(itemClickListener)
        avatarRenderer.render(matrixItem, holder.avatarImageView)
        holder.avatarImageView.contentDescription = matrixItem.getBestName()
        holder.titleTextView.text = title
        holder.dateTextView.text = date
        if (rootMessageDeleted) {
            holder.rootMessageTextView.text = holder.view.context.getString(CommonStrings.event_redacted)
            holder.rootMessageTextView.setTextColor(ThemeUtils.getColor(holder.view.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_secondary))
            holder.rootMessageTextView.setLeftDrawable(R.drawable.ic_trash_16, chat.progressive.lib.ui.styles.R.attr.vctr_content_tertiary)
            holder.rootMessageTextView.compoundDrawablePadding = DimensionConverter(holder.view.context.resources).dpToPx(10)
        } else {
            holder.rootMessageTextView.setTextColor(ThemeUtils.getColor(holder.view.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_primary))
            holder.rootMessageTextView.text = rootMessage
            holder.rootMessageTextView.clearDrawables()
        }
        // Last message summary
        lastMessageMatrixItem?.let {
            avatarRenderer.render(it, holder.lastMessageAvatarImageView)
        }
        holder.lastMessageAvatarImageView.contentDescription = lastMessageMatrixItem?.getBestName()
        holder.lastMessageTextView.text = lastMessage
        holder.lastMessageCounterTextView.text = lastMessageCounter
        renderNotificationState(holder)
    }

    private fun renderNotificationState(holder: Holder) {
        when (threadNotificationState) {
            ThreadNotificationState.NEW_MESSAGE -> {
                holder.unreadImageView.isVisible = true
                holder.unreadImageView.setColorFilter(ContextCompat.getColor(holder.view.context, chat.progressive.lib.ui.styles.R.color.palette_gray_200))
            }
            ThreadNotificationState.NEW_HIGHLIGHTED_MESSAGE -> {
                holder.unreadImageView.isVisible = true
                holder.unreadImageView.setColorFilter(ContextCompat.getColor(holder.view.context, chat.progressive.lib.ui.styles.R.color.palette_vermilion))
            }
            else -> {
                holder.unreadImageView.isVisible = false
            }
        }
    }

    class Holder : ProgressiveEpoxyHolder() {
        val avatarImageView by bind<ImageView>(R.id.threadSummaryAvatarImageView)
        val titleTextView by bind<TextView>(R.id.threadSummaryTitleTextView)
        val dateTextView by bind<TextView>(R.id.threadSummaryDateTextView)
        val rootMessageTextView by bind<TextView>(R.id.threadSummaryRootMessageTextView)
        val lastMessageAvatarImageView by bind<ImageView>(R.id.messageThreadSummaryAvatarImageView)
        val lastMessageCounterTextView by bind<TextView>(R.id.messageThreadSummaryCounterTextView)
        val lastMessageTextView by bind<TextView>(R.id.messageThreadSummaryInfoTextView)
        val unreadImageView by bind<ImageView>(R.id.threadSummaryUnreadImageView)
        val rootView by bind<ConstraintLayout>(R.id.threadSummaryRootConstraintLayout)
    }
}
