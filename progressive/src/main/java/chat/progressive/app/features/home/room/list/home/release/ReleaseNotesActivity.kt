/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list.home.release

import android.view.View
import androidx.lifecycle.lifecycleScope
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.addFragment
import chat.progressive.app.core.platform.ScreenOrientationLocker
import chat.progressive.app.core.platform.ProgressiveActivity
import chat.progressive.app.databinding.ActivitySimpleBinding
import kotlinx.coroutines.launch
import javax.inject.Inject

@AndroidEntryPoint
class ReleaseNotesActivity : ProgressiveActivity<ActivitySimpleBinding>() {

    @Inject lateinit var orientationLocker: ScreenOrientationLocker
    @Inject lateinit var releaseNotesPreferencesStore: ReleaseNotesPreferencesStore

    override fun getBinding() = ActivitySimpleBinding.inflate(layoutInflater)

    override fun getCoordinatorLayout() = views.coordinatorLayout

    override val rootView: View
        get() = views.coordinatorLayout

    override fun initUiAndData() {
        orientationLocker.lockPhonesToPortrait(this)
        if (isFirstCreation()) {
            addFragment(views.simpleFragmentContainer, ReleaseNotesFragment::class.java)
        }
    }

    override fun onResume() {
        super.onResume()
        lifecycleScope.launch {
            releaseNotesPreferencesStore.setAppLayoutOnboardingShown(true)
        }
    }
}
