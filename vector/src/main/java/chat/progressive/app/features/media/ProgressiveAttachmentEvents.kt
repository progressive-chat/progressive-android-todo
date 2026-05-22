/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.media

import chat.progressive.app.core.platform.VectorViewEvents

sealed class ProgressiveAttachmentEvents : VectorViewEvents {
    data class ErrorDownloadingMedia(val error: Throwable) : ProgressiveAttachmentEvents()
}
