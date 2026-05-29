/*
 * Copyright 2018-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */
package chat.progressive.app.features.settings.troubleshoot

import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.features.settings.ProgressiveBasePreferences
import chat.progressive.lib.strings.CommonStrings
import javax.inject.Inject

/**
 * Checks if notifications are enable in the system settings for this app.
 */
class TestDeviceSettings @Inject constructor(
        private val progressivePreferences: ProgressiveBasePreferences,
        private val stringProvider: StringProvider
) :
        TroubleshootTest(CommonStrings.settings_troubleshoot_test_device_settings_title) {

    override fun perform(testParameters: TestParameters) {
        if (progressivePreferences.areNotificationEnabledForDevice()) {
            description = stringProvider.getString(CommonStrings.settings_troubleshoot_test_device_settings_success)
            quickFix = null
            status = TestStatus.SUCCESS
        } else {
            quickFix = object : TroubleshootQuickFix(CommonStrings.settings_troubleshoot_test_device_settings_quickfix) {
                override fun doFix() {
                    progressivePreferences.setNotificationEnabledForDevice(true)
                    manager?.retry(testParameters)
                }
            }
            description = stringProvider.getString(CommonStrings.settings_troubleshoot_test_device_settings_failed)
            status = TestStatus.FAILED
        }
    }
}
