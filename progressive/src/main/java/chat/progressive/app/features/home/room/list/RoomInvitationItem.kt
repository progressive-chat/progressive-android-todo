/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list

import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.setTextOrHide
import chat.progressive.app.core.platform.ButtonStateView
import chat.progressive.app.features.displayname.getBestName
import chat.progressive.app.features.home.AvatarRenderer
import chat.progressive.app.features.invite.InviteButtonStateBinder
import org.matrix.android.sdk.api.session.room.members.ChangeMembershipState
import org.matrix.android.sdk.api.util.MatrixItem

@EpoxyModelClass
abstract class RoomInvitationItem : ProgressiveEpoxyModel<RoomInvitationItem.Holder>(R.layout.item_room_invitation) {

    @EpoxyAttribute lateinit var avatarRenderer: AvatarRenderer
    @EpoxyAttribute lateinit var matrixItem: MatrixItem
    @EpoxyAttribute var secondLine: String? = null
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var listener: ClickListener? = null
    @EpoxyAttribute lateinit var changeMembershipState: ChangeMembershipState
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var acceptListener: ClickListener? = null
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var rejectListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.rootView.onClick(listener)
        holder.acceptView.commonClicked = acceptListener
        holder.rejectView.commonClicked = rejectListener
        InviteButtonStateBinder.bind(holder.acceptView, holder.rejectView, changeMembershipState)
        holder.titleView.text = matrixItem.getBestName()
        holder.subtitleView.setTextOrHide(secondLine)
        avatarRenderer.render(matrixItem, holder.avatarImageView)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val titleView by bind<TextView>(R.id.roomInvitationNameView)
        val subtitleView by bind<TextView>(R.id.roomInvitationSubTitle)
        val acceptView by bind<ButtonStateView>(R.id.roomInvitationAccept)
        val rejectView by bind<ButtonStateView>(R.id.roomInvitationReject)
        val avatarImageView by bind<ImageView>(R.id.roomInvitationAvatarImageView)
        val rootView by bind<ViewGroup>(R.id.itemRoomInvitationLayout)
    }
}
