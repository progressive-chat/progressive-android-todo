/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.devices.v2.details

import chat.progressive.app.core.session.clientinfo.MatrixClientInfoContent
import org.matrix.android.sdk.api.extensions.orFalse
import javax.inject.Inject

class CheckIfSectionApplicationIsVisibleUseCase @Inject constructor() {

    fun execute(matrixClientInfoContent: MatrixClientInfoContent?): Boolean {
        return matrixClientInfoContent?.name?.isNotEmpty().orFalse() ||
                matrixClientInfoContent?.version?.isNotEmpty().orFalse() ||
                matrixClientInfoContent?.url?.isNotEmpty().orFalse()
    }
}
