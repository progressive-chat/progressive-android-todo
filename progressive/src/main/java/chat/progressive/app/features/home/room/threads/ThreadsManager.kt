/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.threads

import android.app.Activity
import android.text.Spanned
import androidx.annotation.StringRes
import androidx.core.text.HtmlCompat
import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.features.MainActivity
import chat.progressive.app.features.MainActivityArgs
import chat.progressive.app.features.settings.ProgressiveBasePreferences
import chat.progressive.lib.strings.CommonStrings
import org.matrix.android.sdk.api.settings.LightweightSettingsStorage
import javax.inject.Inject

/**
 * The class is responsible for handling thread specific tasks.
 */
class ThreadsManager @Inject constructor(
        private val progressivePreferences: ProgressiveBasePreferences,
        private val lightweightSettingsStorage: LightweightSettingsStorage,
        private val stringProvider: StringProvider
) {

    /**
     * Enable threads and invoke an initial sync. The initial sync is mandatory in order to change
     * the already saved DB schema for already received messages
     */
    fun enableThreadsAndRestart(activity: Activity) {
        progressivePreferences.setThreadMessagesEnabled()
        lightweightSettingsStorage.setThreadMessagesEnabled(progressivePreferences.areThreadMessagesEnabled())
        MainActivity.restartApp(activity, MainActivityArgs(clearCache = true))
    }

    /**
     * Generates and return an Html spanned string to be rendered especially in dialogs.
     */
    private fun generateLearnMoreHtmlString(@StringRes messageId: Int): Spanned {
        val learnMore = stringProvider.getString(CommonStrings.action_learn_more)
        val learnMoreUrl = stringProvider.getString(chat.progressive.app.config.R.string.threads_learn_more_url)
        val href = "<a href='$learnMoreUrl'>$learnMore</a>.<br><br>"
        val message = stringProvider.getString(messageId, href)
        return HtmlCompat.fromHtml(message, HtmlCompat.FROM_HTML_MODE_LEGACY)
    }

    fun getBetaEnableThreadsMessage(): Spanned =
            generateLearnMoreHtmlString(CommonStrings.threads_beta_enable_notice_message)

    fun getLabsEnableThreadsMessage(): Spanned =
            generateLearnMoreHtmlString(CommonStrings.threads_labs_enable_notice_message)
}
