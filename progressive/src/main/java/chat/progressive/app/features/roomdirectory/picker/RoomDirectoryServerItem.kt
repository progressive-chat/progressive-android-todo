/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomdirectory.picker

import android.view.View
import android.widget.TextView
import androidx.core.view.isVisible
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.setTextOrHide

@EpoxyModelClass
abstract class RoomDirectoryServerItem : ProgressiveEpoxyModel<RoomDirectoryServerItem.Holder>(R.layout.item_room_directory_server) {

    @EpoxyAttribute
    var serverName: String? = null

    @EpoxyAttribute
    var serverDescription: String? = null

    @EpoxyAttribute
    var canRemove: Boolean = false

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var removeListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.nameView.text = serverName
        holder.descriptionView.setTextOrHide(serverDescription)
        holder.deleteView.isVisible = canRemove
        holder.deleteView.onClick(removeListener)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val nameView by bind<TextView>(R.id.itemRoomDirectoryServerName)
        val descriptionView by bind<TextView>(R.id.itemRoomDirectoryServerDescription)
        val deleteView by bind<View>(R.id.itemRoomDirectoryServerRemove)
    }
}
