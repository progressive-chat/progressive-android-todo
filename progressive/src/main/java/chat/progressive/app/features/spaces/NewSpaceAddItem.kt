/*
 * Copyright 2021-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.spaces

import android.content.res.ColorStateList
import android.widget.ImageView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.features.themes.ThemeUtils

@EpoxyModelClass
abstract class NewSpaceAddItem : ProgressiveEpoxyModel<NewSpaceAddItem.Holder>(R.layout.item_new_space_add) {

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var listener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.view.onClick(listener)

        holder.plus.imageTintList = ColorStateList.valueOf(ThemeUtils.getColor(holder.view.context, chat.progressive.lib.ui.styles.R.attr.vctr_content_primary))
    }

    class Holder : ProgressiveEpoxyHolder() {
        val plus by bind<ImageView>(R.id.plus)
    }
}
