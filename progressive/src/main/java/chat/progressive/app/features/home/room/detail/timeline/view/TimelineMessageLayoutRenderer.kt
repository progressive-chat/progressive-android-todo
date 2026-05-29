/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.timeline.view

import chat.progressive.app.features.home.room.detail.timeline.style.TimelineMessageLayout

interface TimelineMessageLayoutRenderer {
    fun renderMessageLayout(messageLayout: TimelineMessageLayout)
}
