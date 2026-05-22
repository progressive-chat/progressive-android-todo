/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.glide

import com.bumptech.glide.load.Option
import org.matrix.android.sdk.api.session.crypto.attachments.ElementToDecrypt

const val ElementToDecryptOptionKey = "chat.progressive.app.core.glide.ElementToDecrypt"

val ELEMENT_TO_DECRYPT = Option.memory(
        ElementToDecryptOptionKey, ElementToDecrypt("", "", "")
)
