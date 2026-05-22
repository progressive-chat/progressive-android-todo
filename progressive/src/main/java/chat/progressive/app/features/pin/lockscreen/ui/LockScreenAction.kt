/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.pin.lockscreen.ui

import androidx.fragment.app.FragmentActivity
import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class LockScreenAction : ProgressiveViewModelAction {
    data class PinCodeEntered(val value: String) : LockScreenAction()
    data class ShowBiometricPrompt(val callingActivity: FragmentActivity) : LockScreenAction()
    object OnUIReady : LockScreenAction()
}
