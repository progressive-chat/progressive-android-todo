/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.search

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class SearchAction : ProgressiveViewModelAction {
    data class SearchWith(val searchTerm: String) : SearchAction()
    object LoadMore : SearchAction()
    object Retry : SearchAction()
}
