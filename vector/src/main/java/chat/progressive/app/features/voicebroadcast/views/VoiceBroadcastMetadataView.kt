/*
 * Copyright 2022-2024 New Vector Ltd.
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Element-Commercial
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.voicebroadcast.views

import android.content.Context
import android.content.res.TypedArray
import android.util.AttributeSet
import android.view.LayoutInflater
import android.widget.LinearLayout
import androidx.core.content.res.use
import chat.progressive.app.R
import chat.progressive.app.databinding.ViewVoiceBroadcastMetadataBinding

class VoiceBroadcastMetadataView @JvmOverloads constructor(
        context: Context,
        attrs: AttributeSet? = null,
        defStyleAttr: Int = 0
) : LinearLayout(context, attrs, defStyleAttr) {

    private val views = ViewVoiceBroadcastMetadataBinding.inflate(
            LayoutInflater.from(context),
            this
    )

    var value: String
        get() = views.metadataText.text.toString()
        set(newValue) {
            views.metadataText.text = newValue
        }

    init {
        context.obtainStyledAttributes(
                attrs,
                chat.progressive.lib.ui.styles.R.styleable.VoiceBroadcastMetadataView,
                0,
                0
        ).use {
            setIcon(it)
            setValue(it)
        }
    }

    private fun setIcon(typedArray: TypedArray) {
        val icon = typedArray.getDrawable(chat.progressive.lib.ui.styles.R.styleable.VoiceBroadcastMetadataView_metadataIcon)
        views.metadataIcon.setImageDrawable(icon)
    }

    private fun setValue(typedArray: TypedArray) {
        val value = typedArray.getString(chat.progressive.lib.ui.styles.R.styleable.VoiceBroadcastMetadataView_metadataValue)
        views.metadataText.text = value
    }
}
