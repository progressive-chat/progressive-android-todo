/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.dialogs

import androidx.fragment.app.Fragment
import chat.progressive.app.core.resources.ColorProvider
import chat.progressive.app.features.settings.ProgressiveBasePreferences
import chat.progressive.lib.core.utils.timer.Clock
import javax.inject.Inject

class GalleryOrCameraDialogHelperFactory @Inject constructor(
        private val colorProvider: ColorProvider,
        private val clock: Clock,
        private val progressivePreferences: ProgressiveBasePreferences,
) {
    fun create(fragment: Fragment, skipCrop: Boolean = false): GalleryOrCameraDialogHelper {
        return GalleryOrCameraDialogHelper(fragment, colorProvider, clock, progressivePreferences, skipCrop)
    }
}
