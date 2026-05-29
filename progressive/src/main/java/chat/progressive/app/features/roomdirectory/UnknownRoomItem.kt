/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomdirectory

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
import chat.progressive.app.features.home.AvatarRenderer
import org.matrix.android.sdk.api.util.MatrixItem

@EpoxyModelClass
abstract class UnknownRoomItem : ProgressiveEpoxyModel<UnknownRoomItem.Holder>(R.layout.item_unknown_room) {

    @EpoxyAttribute
    lateinit var avatarRenderer: AvatarRenderer

    @EpoxyAttribute
    lateinit var matrixItem: MatrixItem

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var globalListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.rootView.onClick(globalListener)
        avatarRenderer.render(matrixItem, holder.avatarView)
        holder.nameView.text = matrixItem.displayName
    }

    class Holder : ProgressiveEpoxyHolder() {
        val rootView by bind<ViewGroup>(R.id.itemUnknownRoomLayout)
        val avatarView by bind<ImageView>(R.id.itemUnknownRoomAvatar)
        val nameView by bind<TextView>(R.id.itemUnknownRoomName)
    }
}
