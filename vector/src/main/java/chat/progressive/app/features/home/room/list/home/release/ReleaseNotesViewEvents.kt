/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.list.home.release

import chat.progressive.app.core.platform.VectorViewEvents

sealed class ReleaseNotesViewEvents : VectorViewEvents {
    object Close : ReleaseNotesViewEvents()
    data class SelectPage(val index: Int) : ReleaseNotesViewEvents()
}
