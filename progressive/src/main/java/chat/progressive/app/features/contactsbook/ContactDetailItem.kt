/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.contactsbook

import android.widget.TextView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.setTextOrHide

@EpoxyModelClass
abstract class ContactDetailItem : ProgressiveEpoxyModel<ContactDetailItem.Holder>(R.layout.item_contact_detail) {

    @EpoxyAttribute lateinit var threePid: String
    @EpoxyAttribute var matrixId: String? = null

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var clickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.view.onClick(clickListener)
        holder.nameView.text = threePid
        holder.matrixIdView.setTextOrHide(matrixId)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val nameView by bind<TextView>(R.id.contactDetailName)
        val matrixIdView by bind<TextView>(R.id.contactDetailMatrixId)
    }
}
