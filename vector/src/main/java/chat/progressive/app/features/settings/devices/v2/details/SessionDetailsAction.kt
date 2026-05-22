/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.devices.v2.details

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class SessionDetailsAction : ProgressiveViewModelAction {
    data class CopyToClipboard(val content: String) : SessionDetailsAction()
}
