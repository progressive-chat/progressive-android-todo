/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.roomprofile.alias.detail

import com.airbnb.mvrx.MavericksViewModelFactory
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.core.di.MavericksAssistedViewModelFactory
import chat.progressive.app.core.di.hiltMavericksViewModelFactory
import chat.progressive.app.core.platform.EmptyAction
import chat.progressive.app.core.platform.EmptyViewEvents
import chat.progressive.app.core.platform.ProgressiveViewModel
import org.matrix.android.sdk.api.session.Session

class RoomAliasBottomSheetViewModel @AssistedInject constructor(
        @Assisted initialState: RoomAliasBottomSheetState,
        session: Session
) : ProgressiveViewModel<RoomAliasBottomSheetState, EmptyAction, EmptyViewEvents>(initialState) {

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<RoomAliasBottomSheetViewModel, RoomAliasBottomSheetState> {
        override fun create(initialState: RoomAliasBottomSheetState): RoomAliasBottomSheetViewModel
    }

    companion object : MavericksViewModelFactory<RoomAliasBottomSheetViewModel, RoomAliasBottomSheetState> by hiltMavericksViewModelFactory()

    init {
        setState {
            copy(
                    matrixToLink = session.permalinkService().createPermalink(alias)
            )
        }
    }

    override fun handle(action: EmptyAction) {
        // No op
    }
}
