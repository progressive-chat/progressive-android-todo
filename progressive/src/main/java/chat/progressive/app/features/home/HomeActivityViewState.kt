/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home

import com.airbnb.mvrx.MavericksState
import chat.progressive.app.features.onboarding.AuthenticationDescription
import org.matrix.android.sdk.api.session.sync.SyncRequestState

data class HomeActivityViewState(
        val syncRequestState: SyncRequestState = SyncRequestState.Idle,
        val authenticationDescription: AuthenticationDescription? = null,
) : MavericksState
