/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.crypto.verification.epoxy

import android.widget.TextView
import com.airbnb.epoxy.EpoxyAttribute
import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel

/**
 * A action for bottom sheet.
 */
@EpoxyModelClass
abstract class BottomSheetVerificationDecimalCodeItem : ProgressiveEpoxyModel<BottomSheetVerificationDecimalCodeItem.Holder>(
        R.layout.item_verification_decimal_code
) {

    @EpoxyAttribute
    var code: String = ""

    override fun bind(holder: Holder) {
        super.bind(holder)
        holder.code.text = code
    }

    class Holder : ProgressiveEpoxyHolder() {
        val code by bind<TextView>(R.id.itemVerificationDecimalCode)
    }
}
