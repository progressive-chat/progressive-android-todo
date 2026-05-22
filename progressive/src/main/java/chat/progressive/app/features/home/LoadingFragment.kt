/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home

import android.graphics.drawable.AnimationDrawable
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.databinding.FragmentLoadingBinding

@AndroidEntryPoint
class LoadingFragment : ProgressiveFragment<FragmentLoadingBinding>() {

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentLoadingBinding {
        return FragmentLoadingBinding.inflate(inflater, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val background = views.animatedLogoImageView.background
        if (background is AnimationDrawable) {
            background.start()
        }
    }
}
