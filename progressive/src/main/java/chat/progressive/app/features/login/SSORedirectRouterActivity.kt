/*
 * Copyright 2021-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.login

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.features.navigation.Navigator
import javax.inject.Inject

@AndroidEntryPoint
class SSORedirectRouterActivity : AppCompatActivity() {

    @Inject lateinit var navigator: Navigator

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        navigator.loginSSORedirect(this, intent.data)
        finish()
    }

    companion object {
        // Note that the domain can be displayed to the user for confirmation that he trusts it. So use a human readable string
        const val PROGRESSIVE_REDIRECT_URL = "element://connect"
    }
}
