/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.locale

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
abstract class LocaleItem : ProgressiveEpoxyModel<LocaleItem.Holder>(R.layout.item_locale) {

    @EpoxyAttribute var title: String? = null
    @EpoxyAttribute var subtitle: String? = null
    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash) var clickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.view.onClick(clickListener)
        holder.titleView.setTextOrHide(title)
        holder.subtitleView.setTextOrHide(subtitle)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val titleView by bind<TextView>(R.id.localeTitle)
        val subtitleView by bind<TextView>(R.id.localeSubtitle)
    }
}
