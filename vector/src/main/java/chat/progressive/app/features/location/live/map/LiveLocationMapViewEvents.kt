/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.location.live.map

import chat.progressive.app.core.platform.VectorViewEvents
import chat.progressive.app.features.location.LocationData

sealed interface LiveLocationMapViewEvents : VectorViewEvents {
    data class LiveLocationError(val error: Throwable) : LiveLocationMapViewEvents
    data class ZoomToUserLocation(val userLocation: LocationData) : LiveLocationMapViewEvents
    object UserLocationNotAvailableError : LiveLocationMapViewEvents
}
