/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home

import chat.progressive.app.features.settings.ProgressiveBasePreferences
import javax.inject.Inject

class SetNewLoginAlertShownUseCase @Inject constructor(
        private val progressivePreferences: ProgressiveBasePreferences,
) {

    fun execute(deviceIds: List<String>) {
        deviceIds.forEach {
            progressivePreferences.setNewLoginAlertShownForDevice(it)
        }
    }
}
