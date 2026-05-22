/*
 * Copyright 2022-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.spaces

import android.app.Dialog
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import chat.progressive.app.R
import chat.progressive.app.core.extensions.replaceChildFragment
import chat.progressive.app.core.platform.ProgressiveBottomSheet
import chat.progressive.app.databinding.FragmentSpacesBottomSheetBinding
import chat.progressive.app.features.analytics.plan.MobileScreen

class SpaceListBottomSheet : ProgressiveBottomSheet<FragmentSpacesBottomSheetBinding>() {

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentSpacesBottomSheetBinding {
        return FragmentSpacesBottomSheetBinding.inflate(inflater, container, false)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        analyticsScreenName = MobileScreen.ScreenName.SpaceBottomSheet
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        if (savedInstanceState == null) {
            replaceChildFragment(R.id.space_list, SpaceListFragment::class.java)
        }
    }

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        return super.onCreateDialog(savedInstanceState).apply {
            setPeekHeightAsScreenPercentage(0.75f)
        }
    }

    companion object {
        const val TAG = "SpacesBottomSheet"
    }
}
