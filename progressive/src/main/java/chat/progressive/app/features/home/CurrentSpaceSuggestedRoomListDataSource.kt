/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home

import chat.progressive.app.core.utils.BehaviorDataSource
import org.matrix.android.sdk.api.session.room.model.SpaceChildInfo
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class CurrentSpaceSuggestedRoomListDataSource @Inject constructor() : BehaviorDataSource<List<SpaceChildInfo>>()
