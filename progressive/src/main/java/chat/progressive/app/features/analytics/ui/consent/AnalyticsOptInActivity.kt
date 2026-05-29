/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.analytics.ui.consent

import android.view.View
import com.airbnb.mvrx.viewModel
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.addFragment
import chat.progressive.app.core.platform.ScreenOrientationLocker
import chat.progressive.app.core.platform.ProgressiveActivity
import chat.progressive.app.databinding.ActivitySimpleBinding
import javax.inject.Inject

/**
 * Simple container for AnalyticsOptInFragment.
 */
@AndroidEntryPoint
class AnalyticsOptInActivity : ProgressiveActivity<ActivitySimpleBinding>() {

    @Inject lateinit var orientationLocker: ScreenOrientationLocker

    private val viewModel: AnalyticsConsentViewModel by viewModel()

    override fun getBinding() = ActivitySimpleBinding.inflate(layoutInflater)

    override fun getCoordinatorLayout() = views.coordinatorLayout

    override val rootView: View
        get() = views.coordinatorLayout

    override fun initUiAndData() {
        orientationLocker.lockPhonesToPortrait(this)
        if (isFirstCreation()) {
            addFragment(views.simpleFragmentContainer, AnalyticsOptInFragment::class.java)
        }

        viewModel.observeViewEvents {
            when (it) {
                AnalyticsOptInViewEvents.OnDataSaved -> finish()
            }
        }
    }
}
