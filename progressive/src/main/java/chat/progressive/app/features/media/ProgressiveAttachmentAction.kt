/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.media

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import java.io.File

sealed class ProgressiveAttachmentAction : ProgressiveViewModelAction {
    data class DownloadMedia(val file: File) : ProgressiveAttachmentAction()
}
