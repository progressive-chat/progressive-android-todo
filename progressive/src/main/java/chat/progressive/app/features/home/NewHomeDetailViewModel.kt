/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home

import com.airbnb.mvrx.MavericksViewModelFactory
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.core.di.MavericksAssistedViewModelFactory
import chat.progressive.app.core.di.hiltMavericksViewModelFactory
import chat.progressive.app.core.platform.EmptyAction
import chat.progressive.app.core.platform.EmptyViewEvents
import chat.progressive.app.core.platform.ProgressiveViewModel
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach

class NewHomeDetailViewModel @AssistedInject constructor(
        @Assisted initialState: NewHomeDetailViewState,
        private val getSpacesNotificationBadgeStateUseCase: GetSpacesNotificationBadgeStateUseCase,
) : ProgressiveViewModel<NewHomeDetailViewState, EmptyAction, EmptyViewEvents>(initialState) {

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<NewHomeDetailViewModel, NewHomeDetailViewState> {
        override fun create(initialState: NewHomeDetailViewState): NewHomeDetailViewModel
    }

    companion object : MavericksViewModelFactory<NewHomeDetailViewModel, NewHomeDetailViewState> by hiltMavericksViewModelFactory()

    init {
        observeSpacesNotificationBadgeState()
    }

    private fun observeSpacesNotificationBadgeState() {
        getSpacesNotificationBadgeStateUseCase.execute()
                .onEach { badgeState -> setState { copy(spacesNotificationCounterBadgeState = badgeState) } }
                .launchIn(viewModelScope)
    }

    override fun handle(action: EmptyAction) {
        // do nothing
    }
}
