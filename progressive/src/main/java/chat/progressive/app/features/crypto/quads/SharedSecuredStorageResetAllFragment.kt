/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.crypto.quads

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.airbnb.mvrx.activityViewModel
import com.airbnb.mvrx.withState
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.core.extensions.setTextOrHide
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.databinding.FragmentSsssResetAllBinding
import chat.progressive.app.features.roommemberprofile.devices.DeviceListBottomSheet
import chat.progressive.lib.strings.CommonPlurals

@AndroidEntryPoint
class SharedSecuredStorageResetAllFragment :
        ProgressiveFragment<FragmentSsssResetAllBinding>() {

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentSsssResetAllBinding {
        return FragmentSsssResetAllBinding.inflate(inflater, container, false)
    }

    val sharedViewModel: SharedSecureStorageViewModel by activityViewModel()

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        views.ssssResetButtonReset.debouncedClicks {
            sharedViewModel.handle(SharedSecureStorageAction.DoResetAll)
        }

        views.ssssResetButtonCancel.debouncedClicks {
            sharedViewModel.handle(SharedSecureStorageAction.Back)
        }

        views.ssssResetOtherDevices.debouncedClicks {
            withState(sharedViewModel) {
                DeviceListBottomSheet.newInstance(it.userId).show(childFragmentManager, "DEV_LIST")
            }
        }

        sharedViewModel.onEach { state ->
            views.ssssResetOtherDevices.setTextOrHide(
                    state.activeDeviceCount
                            .takeIf { it > 0 }
                            ?.let { resources.getQuantityString(CommonPlurals.secure_backup_reset_devices_you_can_verify, it, it) }
            )
        }
    }
}
