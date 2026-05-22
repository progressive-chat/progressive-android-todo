/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.terms

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class ReviewTermsAction : ProgressiveViewModelAction {
    data class LoadTerms(val preferredLanguageCode: String) : ReviewTermsAction()
    data class MarkTermAsAccepted(val url: String, val accepted: Boolean) : ReviewTermsAction()
    object Accept : ReviewTermsAction()
}
