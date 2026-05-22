/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.onboarding.ftueauth

import android.graphics.Typeface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.core.text.toSpannable
import androidx.core.view.isVisible
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.animations.play
import chat.progressive.app.core.utils.isAnimationEnabled
import chat.progressive.app.core.utils.styleMatchingText
import chat.progressive.app.databinding.FragmentFtueAccountCreatedBinding
import chat.progressive.app.features.onboarding.OnboardingAction
import chat.progressive.app.features.onboarding.OnboardingViewEvents
import chat.progressive.app.features.onboarding.OnboardingViewState
import chat.progressive.lib.strings.CommonStrings

@AndroidEntryPoint
class FtueAuthAccountCreatedFragment :
        AbstractFtueAuthFragment<FragmentFtueAccountCreatedBinding>() {

    private var hasPlayedConfetti = false

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentFtueAccountCreatedBinding {
        return FragmentFtueAccountCreatedBinding.inflate(inflater, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setupViews()
    }

    private fun setupViews() {
        views.accountCreatedPersonalize.debouncedClicks { viewModel.handle(OnboardingAction.PersonalizeProfile) }
        views.accountCreatedTakeMeHome.debouncedClicks { viewModel.handle(OnboardingAction.PostViewEvent(OnboardingViewEvents.OnTakeMeHome)) }
        views.accountCreatedTakeMeHomeCta.debouncedClicks { viewModel.handle(OnboardingAction.PostViewEvent(OnboardingViewEvents.OnTakeMeHome)) }
    }

    override fun updateWithState(state: OnboardingViewState) {
        val userId = state.personalizationState.userId
        val subtitle = getString(CommonStrings.ftue_account_created_subtitle, userId).toSpannable().styleMatchingText(userId, Typeface.BOLD)
        views.accountCreatedSubtitle.text = subtitle
        val canPersonalize = state.personalizationState.supportsPersonalization()
        views.personalizeButtonGroup.isVisible = canPersonalize
        views.takeMeHomeButtonGroup.isVisible = !canPersonalize

        if (!hasPlayedConfetti && requireContext().isAnimationEnabled()) {
            hasPlayedConfetti = true
            views.viewKonfetti.isVisible = true
            views.viewKonfetti.play()
        }
    }

    override fun resetViewModel() {
        // Nothing to do
    }

    override fun onBackPressed(toolbarButton: Boolean): Boolean {
        viewModel.handle(OnboardingAction.PostViewEvent(OnboardingViewEvents.OnTakeMeHome))
        return true
    }
}
