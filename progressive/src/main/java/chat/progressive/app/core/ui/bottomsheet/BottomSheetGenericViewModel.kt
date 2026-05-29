/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.ui.bottomsheet

import com.airbnb.mvrx.MavericksState
import chat.progressive.app.core.platform.EmptyAction
import chat.progressive.app.core.platform.EmptyViewEvents
import chat.progressive.app.core.platform.ProgressiveViewModel

abstract class BottomSheetGenericViewModel<State : MavericksState>(initialState: State) :
        ProgressiveViewModel<State, EmptyAction, EmptyViewEvents>(initialState) {

    override fun handle(action: EmptyAction) {
        // No op
    }
}
