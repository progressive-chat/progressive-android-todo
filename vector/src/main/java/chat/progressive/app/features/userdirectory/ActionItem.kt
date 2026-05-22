/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.userdirectory

import android.widget.ImageView
import android.widget.TextView
import androidx.annotation.DrawableRes
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.setTextOrHide

@EpoxyModelClass
abstract class ActionItem : ProgressiveEpoxyModel<ActionItem.Holder>(R.layout.item_contact_action) {

    @EpoxyAttribute var title: String? = null
    @EpoxyAttribute @DrawableRes var actionIconRes: Int? = null
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var clickAction: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.view.onClick(clickAction)
        // If name is empty, use userId as name and force it being centered
        holder.actionTitleText.setTextOrHide(title)
        if (actionIconRes != null) {
            holder.actionTitleImageView.setImageResource(actionIconRes!!)
        } else {
            holder.actionTitleImageView.setImageDrawable(null)
        }
    }

    class Holder : ProgressiveEpoxyHolder() {
        val actionTitleText by bind<TextView>(R.id.actionTitleText)
        val actionTitleImageView by bind<ImageView>(R.id.actionIconImageView)
    }
}
