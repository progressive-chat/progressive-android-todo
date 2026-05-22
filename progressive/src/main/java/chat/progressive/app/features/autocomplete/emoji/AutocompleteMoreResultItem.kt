/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.autocomplete.emoji

import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel

@EpoxyModelClass
abstract class AutocompleteMoreResultItem : ProgressiveEpoxyModel<AutocompleteMoreResultItem.Holder>(R.layout.item_autocomplete_more_result) {

    class Holder : ProgressiveEpoxyHolder()
}
