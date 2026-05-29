/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.reactions

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class EmojiSearchAction : ProgressiveViewModelAction {
    data class UpdateQuery(val queryString: String) : EmojiSearchAction()
}
