/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.crypto.recover

import android.view.LayoutInflater
import android.view.ViewGroup
import com.airbnb.mvrx.parentFragmentViewModel
import com.airbnb.mvrx.withState
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.setTextOrHide
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.databinding.FragmentBootstrapErrorBinding
import chat.progressive.lib.strings.CommonStrings

@AndroidEntryPoint
class BootstrapErrorFragment :
        ProgressiveFragment<FragmentBootstrapErrorBinding>() {

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentBootstrapErrorBinding {
        return FragmentBootstrapErrorBinding.inflate(inflater, container, false)
    }

    val sharedViewModel: BootstrapSharedViewModel by parentFragmentViewModel()

    override fun invalidate() = withState(sharedViewModel) { state ->
        when (state.step) {
            is BootstrapStep.Error -> {
                views.bootstrapDescriptionText.setTextOrHide(errorFormatter.toHumanReadable(state.step.error))
            }
            else -> {
                // Should not happen, show a generic error
                views.bootstrapDescriptionText.setTextOrHide(getString(CommonStrings.unknown_error))
            }
        }
        views.bootstrapRetryButton.onClick {
            sharedViewModel.handle(BootstrapActions.Retry)
        }
    }
}
