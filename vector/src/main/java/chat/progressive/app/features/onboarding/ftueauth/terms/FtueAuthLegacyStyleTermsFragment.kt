/*
 * Copyright 2018-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.onboarding.ftueauth.terms

import android.os.Bundle
import android.os.Parcelable
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.airbnb.mvrx.args
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.cleanup
import chat.progressive.app.core.extensions.configureWith
import chat.progressive.app.core.extensions.toReducedUrl
import chat.progressive.app.core.utils.openUrlInChromeCustomTab
import chat.progressive.app.databinding.FragmentLoginTermsBinding
import chat.progressive.app.features.login.terms.LocalizedFlowDataLoginTermsChecked
import chat.progressive.app.features.login.terms.LoginTermsViewState
import chat.progressive.app.features.login.terms.PolicyController
import chat.progressive.app.features.onboarding.OnboardingAction
import chat.progressive.app.features.onboarding.OnboardingViewState
import chat.progressive.app.features.onboarding.RegisterAction
import chat.progressive.app.features.onboarding.ftueauth.AbstractFtueAuthFragment
import kotlinx.parcelize.Parcelize
import org.matrix.android.sdk.api.auth.data.LocalizedFlowDataLoginTerms
import javax.inject.Inject

@Parcelize
data class FtueAuthTermsLegacyStyleFragmentArgument(
        val localizedFlowDataLoginTerms: List<LocalizedFlowDataLoginTerms>
) : Parcelable

/**
 * LoginTermsFragment displays the list of policies the user has to accept.
 */
@AndroidEntryPoint
class FtueAuthLegacyStyleTermsFragment :
        AbstractFtueAuthFragment<FragmentLoginTermsBinding>(),
        PolicyController.PolicyControllerListener {

    @Inject lateinit var policyController: PolicyController

    private val params: FtueAuthTermsLegacyStyleFragmentArgument by args()

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentLoginTermsBinding {
        return FragmentLoginTermsBinding.inflate(inflater, container, false)
    }

    private var loginTermsViewState: LoginTermsViewState = LoginTermsViewState(emptyList())

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        setupViews()
        views.loginTermsPolicyList.configureWith(policyController)
        policyController.listener = this

        val list = ArrayList<LocalizedFlowDataLoginTermsChecked>()

        params.localizedFlowDataLoginTerms
                .forEach {
                    list.add(LocalizedFlowDataLoginTermsChecked(it))
                }

        loginTermsViewState = LoginTermsViewState(list)
    }

    private fun setupViews() {
        views.loginTermsSubmit.setOnClickListener { submit() }
    }

    override fun onDestroyView() {
        views.loginTermsPolicyList.cleanup()
        policyController.listener = null
        super.onDestroyView()
    }

    private fun renderState() {
        policyController.setData(loginTermsViewState.localizedFlowDataLoginTermsChecked)
        views.loginTermsSubmit.isEnabled = loginTermsViewState.allChecked()
    }

    override fun setChecked(localizedFlowDataLoginTerms: LocalizedFlowDataLoginTerms, isChecked: Boolean) {
        if (isChecked) {
            loginTermsViewState.check(localizedFlowDataLoginTerms)
        } else {
            loginTermsViewState.uncheck(localizedFlowDataLoginTerms)
        }

        renderState()
    }

    override fun openPolicy(localizedFlowDataLoginTerms: LocalizedFlowDataLoginTerms) {
        localizedFlowDataLoginTerms.localizedUrl
                ?.takeIf { it.isNotBlank() }
                ?.let {
                    openUrlInChromeCustomTab(requireContext(), null, it)
                }
    }

    private fun submit() {
        viewModel.handle(OnboardingAction.PostRegisterAction(RegisterAction.AcceptTerms))
    }

    override fun updateWithState(state: OnboardingViewState) {
        policyController.homeServer = state.selectedHomeserver.userFacingUrl.toReducedUrl()
        renderState()
    }

    override fun resetViewModel() {
        viewModel.handle(OnboardingAction.ResetAuthenticationAttempt)
    }
}
