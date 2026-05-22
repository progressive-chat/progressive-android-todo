/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package im.vector.app.features.home

import im.vector.app.features.settings.ProgressiveBasePreferences
import im.vector.lib.core.utils.timer.Clock
import javax.inject.Inject

class SetUnverifiedSessionsAlertShownUseCase @Inject constructor(
        private val progressivePreferences: ProgressiveBasePreferences,
        private val clock: Clock,
) {

    fun execute(deviceIds: List<String>) {
        val epochMillis = clock.epochMillis()
        deviceIds.forEach {
            progressivePreferences.setUnverifiedSessionsAlertLastShownMillis(it, epochMillis)
        }
    }
}
