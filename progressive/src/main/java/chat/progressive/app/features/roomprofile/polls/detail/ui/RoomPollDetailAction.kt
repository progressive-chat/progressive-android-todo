/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.polls.detail.ui

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed interface RoomPollDetailAction : ProgressiveViewModelAction {
    data class Vote(val pollEventId: String, val optionId: String) : RoomPollDetailAction
}
