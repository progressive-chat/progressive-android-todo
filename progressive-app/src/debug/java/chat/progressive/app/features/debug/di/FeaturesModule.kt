/*
 * Copyright 2021-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.debug.di

import android.content.Context
import dagger.Binds
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import chat.progressive.app.features.DefaultVectorFeatures
import chat.progressive.app.features.DefaultVectorOverrides
import chat.progressive.app.features.VectorFeatures
import chat.progressive.app.features.VectorOverrides
import chat.progressive.app.features.debug.features.DebugProgressiveFeatures
import chat.progressive.app.features.debug.features.DebugProgressiveOverrides

@InstallIn(SingletonComponent::class)
@Module
interface FeaturesModule {

    @Binds
    fun bindFeatures(debugFeatures: DebugProgressiveFeatures): VectorFeatures

    @Binds
    fun bindOverrides(debugOverrides: DebugProgressiveOverrides): VectorOverrides

    companion object {

        @Provides
        fun providesDefaultVectorFeatures(): DefaultVectorFeatures {
            return DefaultVectorFeatures()
        }

        @Provides
        fun providesDebugProgressiveFeatures(context: Context, defaultVectorFeatures: DefaultVectorFeatures): DebugProgressiveFeatures {
            return DebugProgressiveFeatures(context, defaultVectorFeatures)
        }

        @Provides
        fun providesDefaultVectorOverrides(): DefaultVectorOverrides {
            return DefaultVectorOverrides()
        }

        @Provides
        fun providesDebugProgressiveOverrides(context: Context): DebugProgressiveOverrides {
            return DebugProgressiveOverrides(context)
        }
    }
}
