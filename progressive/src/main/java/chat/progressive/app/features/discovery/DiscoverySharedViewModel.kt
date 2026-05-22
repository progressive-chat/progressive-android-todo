/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.discovery

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import chat.progressive.app.core.extensions.postLiveEvent
import chat.progressive.app.core.utils.LiveEvent
import javax.inject.Inject

class DiscoverySharedViewModel @Inject constructor() : ViewModel() {
    var navigateEvent = MutableLiveData<LiveEvent<DiscoverySharedViewModelAction>>()

    fun requestChangeToIdentityServer(serverUrl: String) {
        navigateEvent.postLiveEvent(DiscoverySharedViewModelAction.ChangeIdentityServer(serverUrl))
    }
}
