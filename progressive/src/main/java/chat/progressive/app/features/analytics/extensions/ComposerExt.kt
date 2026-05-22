/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.analytics.extensions

import chat.progressive.app.features.analytics.plan.Composer
import chat.progressive.app.features.home.room.detail.composer.MessageComposerViewState
import chat.progressive.app.features.home.room.detail.composer.SendMode

fun MessageComposerViewState.toAnalyticsComposer(): Composer =
        Composer(
                inThread = isInThreadTimeline(),
                isEditing = sendMode is SendMode.Edit,
                isReply = sendMode is SendMode.Reply,
                messageType = Composer.MessageType.Text,
                startsThread = startsThread,
        )
