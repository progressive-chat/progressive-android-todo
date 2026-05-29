/*
 * Copyright 2020-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.locale

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import java.util.Locale

sealed class LocalePickerAction : ProgressiveViewModelAction {
    data class SelectLocale(val locale: Locale) : LocalePickerAction()
}
