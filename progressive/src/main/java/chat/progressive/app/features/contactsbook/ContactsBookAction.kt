/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.contactsbook

import chat.progressive.app.core.platform.ProgressiveViewModelAction

sealed class ContactsBookAction : ProgressiveViewModelAction {
    data class FilterWith(val filter: String) : ContactsBookAction()
    data class OnlyBoundContacts(val onlyBoundContacts: Boolean) : ContactsBookAction()
    object UserConsentRequest : ContactsBookAction()
    object UserConsentGranted : ContactsBookAction()
}
