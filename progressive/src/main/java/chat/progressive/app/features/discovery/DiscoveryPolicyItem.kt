/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.discovery

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
abstract class DiscoveryPolicyItem : ProgressiveEpoxyModel<DiscoveryPolicyItem.Holder>(R.layout.item_discovery_policy) {

    @EpoxyAttribute
    var name: String? = null

    @EpoxyAttribute
    var url: String? = null

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var clickListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.title.text = name
        holder.url.setTextOrHide(url)
        holder.view.onClick(clickListener)
    }

    class Holder : ProgressiveEpoxyHolder() {
        val title by bind<TextView>(R.id.discovery_policy_name)
        val url by bind<TextView>(R.id.discovery_policy_url)
    }
}
