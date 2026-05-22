/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.di

import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import chat.progressive.app.BuildConfig
import chat.progressive.app.config.Analytics
import chat.progressive.app.config.Config
import chat.progressive.app.config.KeySharingStrategy
import chat.progressive.app.features.analytics.AnalyticsConfig
import chat.progressive.app.features.call.webrtc.VoipConfig
import chat.progressive.app.features.crypto.keysrequest.OutboundSessionKeySharingStrategy
import chat.progressive.app.features.home.room.detail.composer.voice.VoiceMessageConfig
import chat.progressive.app.features.location.LocationSharingConfig
import chat.progressive.app.features.raw.wellknown.CryptoConfig

@InstallIn(SingletonComponent::class)
@Module
object ConfigurationModule {

    @Provides
    fun providesAnalyticsConfig(): AnalyticsConfig {
        val config: Analytics = when (BuildConfig.BUILD_TYPE) {
            "debug" -> Config.DEBUG_ANALYTICS_CONFIG
            "nightly" -> Config.NIGHTLY_ANALYTICS_CONFIG
            "release" -> Config.RELEASE_ANALYTICS_CONFIG
            else -> throw IllegalStateException("Unhandled build type: ${BuildConfig.BUILD_TYPE}")
        }
        return when (config) {
            Analytics.Disabled -> AnalyticsConfig(isEnabled = false, "", "", "", "", "")
            is Analytics.Enabled -> AnalyticsConfig(
                    isEnabled = true,
                    postHogHost = config.postHogHost,
                    postHogApiKey = config.postHogApiKey,
                    policyLink = config.policyLink,
                    sentryDSN = config.sentryDSN,
                    sentryEnvironment = config.sentryEnvironment
            )
        }
    }

    @Provides
    fun providesVoiceMessageConfig() = VoiceMessageConfig(
            lengthLimitMs = Config.VOICE_MESSAGE_LIMIT_MS
    )

    @Provides
    fun providesCryptoConfig() = CryptoConfig(
            fallbackKeySharingStrategy = when (Config.KEY_SHARING_STRATEGY) {
                KeySharingStrategy.WhenSendingEvent -> OutboundSessionKeySharingStrategy.WhenSendingEvent
                KeySharingStrategy.WhenEnteringRoom -> OutboundSessionKeySharingStrategy.WhenEnteringRoom
                KeySharingStrategy.WhenTyping -> OutboundSessionKeySharingStrategy.WhenTyping
            }
    )

    @Provides
    fun providesLocationSharingConfig() = LocationSharingConfig(
            mapTilerKey = Config.LOCATION_MAP_TILER_KEY,
    )

    @Provides
    fun providesVoipConfig() = VoipConfig(
            handleCallAssertedIdentityEvents = Config.HANDLE_CALL_ASSERTED_IDENTITY_EVENTS
    )
}
