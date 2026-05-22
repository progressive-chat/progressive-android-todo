/*
 * Copyright 2022-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.labs

import com.airbnb.mvrx.MavericksViewModelFactory
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.core.di.ActiveSessionHolder
import chat.progressive.app.core.di.MavericksAssistedViewModelFactory
import chat.progressive.app.core.di.hiltMavericksViewModelFactory
import chat.progressive.app.core.platform.EmptyViewEvents
import chat.progressive.app.core.platform.ProgressiveViewModel
import chat.progressive.app.core.session.clientinfo.DeleteMatrixClientInfoUseCase
import chat.progressive.app.core.session.clientinfo.UpdateMatrixClientInfoUseCase
import kotlinx.coroutines.launch

class VectorSettingsLabsViewModel @AssistedInject constructor(
        @Assisted initialState: VectorSettingsLabsViewState,
        private val activeSessionHolder: ActiveSessionHolder,
        private val updateMatrixClientInfoUseCase: UpdateMatrixClientInfoUseCase,
        private val deleteMatrixClientInfoUseCase: DeleteMatrixClientInfoUseCase,
) : ProgressiveViewModel<VectorSettingsLabsViewState, VectorSettingsLabsAction, EmptyViewEvents>(initialState) {

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<VectorSettingsLabsViewModel, VectorSettingsLabsViewState> {
        override fun create(initialState: VectorSettingsLabsViewState): VectorSettingsLabsViewModel
    }

    companion object : MavericksViewModelFactory<VectorSettingsLabsViewModel, VectorSettingsLabsViewState> by hiltMavericksViewModelFactory()

    override fun handle(action: VectorSettingsLabsAction) {
        when (action) {
            VectorSettingsLabsAction.UpdateClientInfo -> handleUpdateClientInfo()
            VectorSettingsLabsAction.DeleteRecordedClientInfo -> handleDeleteRecordedClientInfo()
        }
    }

    private fun handleUpdateClientInfo() {
        viewModelScope.launch {
            activeSessionHolder.getSafeActiveSession()
                    ?.let { session ->
                        updateMatrixClientInfoUseCase.execute(session)
                    }
        }
    }

    private fun handleDeleteRecordedClientInfo() {
        viewModelScope.launch {
            deleteMatrixClientInfoUseCase.execute()
        }
    }
}
