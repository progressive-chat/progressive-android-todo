/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.media

import com.airbnb.mvrx.MavericksViewModelFactory
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.core.di.MavericksAssistedViewModelFactory
import chat.progressive.app.core.di.hiltMavericksViewModelFactory
import chat.progressive.app.core.platform.ProgressiveDummyViewState
import chat.progressive.app.core.platform.ProgressiveViewModel
import chat.progressive.app.features.media.domain.usecase.DownloadMediaUseCase
import chat.progressive.app.features.session.coroutineScope
import kotlinx.coroutines.launch
import org.matrix.android.sdk.api.session.Session

class ProgressiveAttachmentViewModel @AssistedInject constructor(
        @Assisted initialState: ProgressiveDummyViewState,
        private val session: Session,
        private val downloadMediaUseCase: DownloadMediaUseCase
) : ProgressiveViewModel<ProgressiveDummyViewState, ProgressiveAttachmentAction, ProgressiveAttachmentEvents>(initialState) {

    @AssistedFactory
    interface Factory : MavericksAssistedViewModelFactory<ProgressiveAttachmentViewModel, ProgressiveDummyViewState> {
        override fun create(initialState: ProgressiveDummyViewState): ProgressiveAttachmentViewModel
    }

    companion object : MavericksViewModelFactory<ProgressiveAttachmentViewModel, ProgressiveDummyViewState> by hiltMavericksViewModelFactory()

    var pendingAction: ProgressiveAttachmentAction? = null

    override fun handle(action: ProgressiveAttachmentAction) {
        when (action) {
            is ProgressiveAttachmentAction.DownloadMedia -> handleDownloadAction(action)
        }
    }

    private fun handleDownloadAction(action: ProgressiveAttachmentAction.DownloadMedia) {
        // launch in the coroutine scope session to avoid binding the coroutine to the lifecycle of the VM
        session.coroutineScope.launch {
            // Success event is handled via a notification inside the use case
            downloadMediaUseCase.execute(action.file)
                    .onFailure { _viewEvents.post(ProgressiveAttachmentEvents.ErrorDownloadingMedia(it)) }
        }
    }
}
