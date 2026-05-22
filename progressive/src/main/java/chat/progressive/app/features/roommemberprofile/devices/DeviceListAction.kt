/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roommemberprofile.devices

import chat.progressive.app.core.platform.ProgressiveViewModelAction
import org.matrix.android.sdk.api.session.crypto.model.CryptoDeviceInfo

sealed class DeviceListAction : ProgressiveViewModelAction {
    data class SelectDevice(val device: CryptoDeviceInfo) : DeviceListAction()
    object DeselectDevice : DeviceListAction()
}
