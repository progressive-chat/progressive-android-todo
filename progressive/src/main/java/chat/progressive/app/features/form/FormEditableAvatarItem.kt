/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.form

import android.net.Uri
import android.view.View
import android.widget.ImageView
import androidx.core.view.isVisible
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import com.bumptech.glide.request.RequestOptions
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ClickListener
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.glide.GlideApp
import chat.progressive.app.features.home.AvatarRenderer
import org.matrix.android.sdk.api.util.MatrixItem

@EpoxyModelClass
abstract class FormEditableAvatarItem : ProgressiveEpoxyModel<FormEditableAvatarItem.Holder>(R.layout.item_editable_avatar) {

    @EpoxyAttribute
    var avatarRenderer: AvatarRenderer? = null

    @EpoxyAttribute
    var matrixItem: MatrixItem? = null

    @EpoxyAttribute
    var enabled: Boolean = true

    @EpoxyAttribute
    var imageUri: Uri? = null

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var clickListener: ClickListener? = null

    @EpoxyAttribute(EpoxyAttribute.Option.DoNotHash)
    var deleteListener: ClickListener? = null

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.imageContainer.onClick(clickListener?.takeIf { enabled })
        if (matrixItem != null) {
            avatarRenderer?.render(matrixItem!!, holder.image)
        } else {
            GlideApp.with(holder.image)
                    .load(imageUri)
                    .apply(RequestOptions.circleCropTransform())
                    .into(holder.image)
        }
        holder.delete.isVisible = enabled && (imageUri != null || matrixItem?.avatarUrl?.isNotEmpty() == true)
        holder.delete.onClick(deleteListener?.takeIf { enabled })
    }

    class Holder : ProgressiveEpoxyHolder() {
        val imageContainer by bind<View>(R.id.itemEditableAvatarImageContainer)
        val image by bind<ImageView>(R.id.itemEditableAvatarImage)
        val delete by bind<View>(R.id.itemEditableAvatarDelete)
    }
}
