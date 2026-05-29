/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.platform

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import chat.progressive.app.core.extensions.postLiveEvent
import chat.progressive.app.core.utils.LiveEvent
import chat.progressive.app.features.configuration.ProgressiveConfiguration
import timber.log.Timber
import javax.inject.Inject

class ConfigurationViewModel @Inject constructor(
        private val vectorConfiguration: ProgressiveConfiguration
) : ViewModel() {

    private var currentConfigurationValue: String? = null

    private val _activityRestarter = MutableLiveData<LiveEvent<Unit>>()
    val activityRestarter: LiveData<LiveEvent<Unit>>
        get() = _activityRestarter

    fun onActivityResumed() {
        if (currentConfigurationValue == null) {
            currentConfigurationValue = vectorConfiguration.getHash()
            Timber.v("Configuration: init to $currentConfigurationValue")
        } else {
            val newHash = vectorConfiguration.getHash()
            Timber.v("Configuration: newHash $newHash")

            if (newHash != currentConfigurationValue) {
                Timber.v("Configuration: recreate the Activity")
                currentConfigurationValue = newHash
                _activityRestarter.postLiveEvent(Unit)
            }
        }
    }
}
