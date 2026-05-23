/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.analytics.itf

import im.vector.app.features.analytics.plan.SuperProperties

interface ProgressiveAnalyticsScreen {
    fun getName(): String
    val embedded: Boolean get() = false
}

interface ProgressiveAnalyticsEvent {
    fun getName(): String
    fun getProperties(): Map<String, Any>? = null
}

