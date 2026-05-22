/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.signout.soft.epoxy

import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel

@EpoxyModelClass
abstract class LoginHeaderItem : ProgressiveEpoxyModel<LoginHeaderItem.Holder>(R.layout.item_login_header) {
    class Holder : ProgressiveEpoxyHolder()
}
