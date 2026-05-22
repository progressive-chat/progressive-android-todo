/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.extensions

import android.view.MenuItem
import androidx.annotation.ColorInt
import androidx.core.text.toSpannable
import chat.progressive.app.core.utils.colorizeMatchingText

fun MenuItem.setTextColor(@ColorInt color: Int) {
    val currentTitle = title.orEmpty().toString()
    title = currentTitle
            .toSpannable()
            .colorizeMatchingText(currentTitle, color)
}
