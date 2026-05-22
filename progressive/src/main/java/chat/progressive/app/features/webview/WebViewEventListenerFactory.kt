/*
 * Copyright 2018-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.webview

import chat.progressive.app.core.platform.ProgressiveActivity
import org.matrix.android.sdk.api.session.Session

interface WebViewEventListenerFactory {

    /**
     * @return an instance of WebViewEventListener
     */
    fun eventListener(activity: ProgressiveActivity<*>, session: Session): WebViewEventListener
}
