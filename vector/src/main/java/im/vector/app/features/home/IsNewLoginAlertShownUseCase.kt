/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package im.vector.app.features.home

import im.vector.app.features.settings.ProgressiveBasePreferences
import javax.inject.Inject

class IsNewLoginAlertShownUseCase @Inject constructor(
        private val progressivePreferences: ProgressiveBasePreferences,
) {

    fun execute(deviceId: String?): Boolean {
        deviceId ?: return false

        return progressivePreferences.isNewLoginAlertShownForDevice(deviceId)
    }
}
