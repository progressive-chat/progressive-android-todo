/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.locale

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.appcompat.app.AppCompatActivity
import com.airbnb.mvrx.fragmentViewModel
import com.airbnb.mvrx.withState
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.cleanup
import chat.progressive.app.core.extensions.configureWith
import chat.progressive.app.core.extensions.restart
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.databinding.FragmentLocalePickerBinding
import chat.progressive.lib.strings.CommonStrings
import java.util.Locale
import javax.inject.Inject

@AndroidEntryPoint
class LocalePickerFragment :
        ProgressiveFragment<FragmentLocalePickerBinding>(),
        LocalePickerController.Listener {

    @Inject lateinit var controller: LocalePickerController

    private val viewModel: LocalePickerViewModel by fragmentViewModel()

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentLocalePickerBinding {
        return FragmentLocalePickerBinding.inflate(inflater, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        views.localeRecyclerView.configureWith(controller)
        controller.listener = this

        viewModel.observeViewEvents {
            when (it) {
                LocalePickerViewEvents.RestartActivity -> {
                    activity?.restart()
                }
            }
        }
    }

    override fun onDestroyView() {
        views.localeRecyclerView.cleanup()
        controller.listener = null
        super.onDestroyView()
    }

    override fun invalidate() = withState(viewModel) { state ->
        controller.setData(state)
    }

    override fun onUseCurrentClicked() {
        // Just close the fragment
        parentFragmentManager.popBackStack()
    }

    override fun onLocaleClicked(locale: Locale) {
        viewModel.handle(LocalePickerAction.SelectLocale(locale))
    }

    override fun onResume() {
        super.onResume()
        (activity as? AppCompatActivity)?.supportActionBar?.setTitle(CommonStrings.settings_select_language)
    }
}
