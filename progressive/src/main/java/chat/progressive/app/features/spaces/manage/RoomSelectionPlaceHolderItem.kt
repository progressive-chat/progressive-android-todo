/*
 * Copyright 2021-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.spaces.manage

import com.airbnb.epoxy.EpoxyModelClass
import chat.progressive.app.R
import chat.progressive.app.core.epoxy.ProgressiveEpoxyHolder
import chat.progressive.app.core.epoxy.ProgressiveEpoxyModel

@EpoxyModelClass
abstract class RoomSelectionPlaceHolderItem : ProgressiveEpoxyModel<RoomSelectionPlaceHolderItem.Holder>(R.layout.item_room_to_add_in_space_placeholder) {
    class Holder : ProgressiveEpoxyHolder()
}
