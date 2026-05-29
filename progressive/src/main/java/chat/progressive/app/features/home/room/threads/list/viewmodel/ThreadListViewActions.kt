/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.threads.list.viewmodel

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed interface ThreadListViewActions : ProgressiveViewModelAction {
    object TryAgain : ThreadListViewActions
}
