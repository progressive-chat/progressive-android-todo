/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.utils

import chat.progressive.app.core.resources.ColorProvider
import org.billcarsonfr.jsonviewer.JSonViewerStyleProvider

fun createJSonViewerStyleProvider(colorProvider: ColorProvider): JSonViewerStyleProvider {
    return JSonViewerStyleProvider(
            keyColor = colorProvider.getColorFromAttribute(com.google.android.material.R.attr.colorPrimary),
            secondaryColor = colorProvider.getColorFromAttribute(chat.progressive.lib.ui.styles.R.attr.vctr_content_secondary),
            stringColor = colorProvider.getColorFromAttribute(chat.progressive.lib.ui.styles.R.attr.vctr_notice_text_color),
            baseColor = colorProvider.getColorFromAttribute(chat.progressive.lib.ui.styles.R.attr.vctr_content_primary),
            booleanColor = colorProvider.getColorFromAttribute(chat.progressive.lib.ui.styles.R.attr.vctr_notice_text_color),
            numberColor = colorProvider.getColorFromAttribute(chat.progressive.lib.ui.styles.R.attr.vctr_notice_text_color)
    )
}
