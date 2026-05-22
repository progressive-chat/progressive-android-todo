/*
 * Copyright 2021-2025 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.legals

import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.features.discovery.ServerPolicy
import chat.progressive.app.features.settings.ProgressiveSettingsUrls
import chat.progressive.lib.strings.CommonStrings
import javax.inject.Inject

class ElementLegals @Inject constructor(
        private val stringProvider: StringProvider
) {
    fun getData(): List<ServerPolicy> {
        return listOf(
                ServerPolicy(stringProvider.getString(CommonStrings.settings_copyright), ProgressiveSettingsUrls.COPYRIGHT),
        )
    }
}
