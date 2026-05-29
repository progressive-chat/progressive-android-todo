/*
 * Copyright 2021-2024 Progressive Chat
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
import chat.progressive.app.core.platform.ProgressiveDummyViewState
import chat.progressive.app.core.platform.ProgressiveViewModel
import chat.progressive.app.features.home.room.detail.timeline.helper.MatrixItemColorProvider
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.onEach
import org.matrix.android.sdk.api.session.Session
import org.matrix.android.sdk.api.session.accountdata.UserAccountDataTypes
import org.matrix.android.sdk.api.session.events.model.toModel
import org.matrix.android.sdk.flow.flow
import org.matrix.android.sdk.flow.unwrap
import timber.log.Timber

class UserColorAccountDataViewModel @AssistedInject constructor(
        @Assisted initialState: ProgressiveDummyViewState,
        private val session: Session,
        private val matrixItemColorProvider: MatrixItemColorProvider
) : ProgressiveViewModel<ProgressiveDummyViewState, EmptyAction, EmptyViewEvents>(initialState) {

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<UserColorAccountDataViewModel, ProgressiveDummyViewState> {
        override fun create(initialState: ProgressiveDummyViewState): UserColorAccountDataViewModel
    }

    companion object : MavericksViewModelFactory<UserColorAccountDataViewModel, ProgressiveDummyViewState> by hiltMavericksViewModelFactory()

    init {
        observeAccountData()
    }

    private fun observeAccountData() {
        session.flow()
                .liveUserAccountData(UserAccountDataTypes.TYPE_OVERRIDE_COLORS)
                .unwrap()
                .map { it.content.toModel<Map<String, String>>() }
                .onEach { userColorAccountDataContent ->
                    if (userColorAccountDataContent == null) {
                        Timber.w("Invalid account data im.vector.setting.override_colors")
                    }
                    matrixItemColorProvider.setOverrideColors(userColorAccountDataContent)
                }
                .launchIn(viewModelScope)
    }

    override fun handle(action: EmptyAction) {
        // No op
    }
}
