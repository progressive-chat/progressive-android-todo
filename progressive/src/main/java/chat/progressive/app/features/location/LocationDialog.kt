/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.location

import androidx.fragment.app.Fragment
import com.google.android.material.dialog.MaterialAlertDialogBuilder
import chat.progressive.lib.strings.CommonStrings

fun Fragment.showUserLocationNotAvailableErrorDialog(onConfirmListener: () -> Unit) {
    MaterialAlertDialogBuilder(requireActivity())
            .setTitle(CommonStrings.location_not_available_dialog_title)
            .setMessage(CommonStrings.location_not_available_dialog_content)
            .setPositiveButton(CommonStrings.ok) { _, _ ->
                onConfirmListener()
            }
            .setCancelable(false)
            .show()
}
