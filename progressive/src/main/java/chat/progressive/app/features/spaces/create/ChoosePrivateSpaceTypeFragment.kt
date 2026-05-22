/*
 * Copyright 2021-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.spaces.create

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.airbnb.mvrx.activityViewModel
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.platform.OnBackPressed
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.databinding.FragmentSpaceCreateChoosePrivateModelBinding
import chat.progressive.lib.strings.CommonStrings
import javax.inject.Inject

@AndroidEntryPoint
class ChoosePrivateSpaceTypeFragment :
        ProgressiveFragment<FragmentSpaceCreateChoosePrivateModelBinding>(),
        OnBackPressed {

    @Inject lateinit var stringProvider: StringProvider

    private val sharedViewModel: CreateSpaceViewModel by activityViewModel()

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?) =
            FragmentSpaceCreateChoosePrivateModelBinding.inflate(layoutInflater, container, false)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        views.justMeButton.onClick {
            sharedViewModel.handle(CreateSpaceAction.SetSpaceTopology(SpaceTopology.JustMe))
        }

        views.teammatesButton.onClick {
            sharedViewModel.handle(CreateSpaceAction.SetSpaceTopology(SpaceTopology.MeAndTeammates))
        }

        sharedViewModel.onEach { state ->
            views.accessInfoHelpText.text = stringProvider.getString(CommonStrings.create_spaces_make_sure_access, state.name ?: "")
        }
    }

    override fun onBackPressed(toolbarButton: Boolean): Boolean {
        sharedViewModel.handle(CreateSpaceAction.OnBackPressed)
        return true
    }
}
