/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.autocomplete.command

import android.content.Context
import androidx.recyclerview.widget.RecyclerView
import dagger.assisted.Assisted
import dagger.assisted.AssistedFactory
import dagger.assisted.AssistedInject
import chat.progressive.app.features.autocomplete.AutocompleteClickListener
import chat.progressive.app.features.autocomplete.RecyclerViewPresenter
import chat.progressive.app.features.command.Command
import chat.progressive.app.features.settings.ProgressiveBasePreferences

class AutocompleteCommandPresenter @AssistedInject constructor(
        @Assisted val isInThreadTimeline: Boolean,
        context: Context,
        private val controller: AutocompleteCommandController,
        private val progressivePreferences: ProgressiveBasePreferences
) :
        RecyclerViewPresenter<Command>(context), AutocompleteClickListener<Command> {

    @AssistedFactory
    interface Factory {
        fun create(isFromThreadTimeline: Boolean): AutocompleteCommandPresenter
    }

    init {
        controller.listener = this
    }

    override fun instantiateAdapter(): RecyclerView.Adapter<*> {
        return controller.adapter
    }

    override fun onItemClick(t: Command) {
        dispatchClick(t)
    }

    override fun onQuery(query: CharSequence?) {
        val data = Command.values()
                .filter {
                    !it.isDevCommand || progressivePreferences.developerMode()
                }
                .filter {
                    if (progressivePreferences.areThreadMessagesEnabled() && isInThreadTimeline) {
                        it.isThreadCommand
                    } else {
                        true
                    }
                }
                .filter {
                    if (query.isNullOrEmpty()) {
                        true
                    } else {
                        it.startsWith(query)
                    }
                }
        controller.setData(data)
    }

    fun clear() {
        controller.listener = null
    }
}
