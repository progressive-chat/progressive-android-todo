/*
 * Copyright 2022-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.settings.devices.v2

import android.content.Context
import android.content.res.TypedArray
import android.util.AttributeSet
import android.view.LayoutInflater
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.content.res.use
import chat.progressive.app.core.extensions.setTextWithColoredPart
import chat.progressive.app.databinding.ViewSessionWarningInfoBinding
import chat.progressive.lib.strings.CommonStrings

class SessionWarningInfoView @JvmOverloads constructor(
        context: Context,
        attrs: AttributeSet? = null,
        defStyleAttr: Int = 0
) : ConstraintLayout(context, attrs, defStyleAttr) {

    private val binding = ViewSessionWarningInfoBinding.inflate(
            LayoutInflater.from(context),
            this
    )

    var onLearnMoreClickListener: (() -> Unit)? = null

    init {
        context.obtainStyledAttributes(
                attrs,
                chat.progressive.lib.ui.styles.R.styleable.SessionWarningInfoView,
                0,
                0
        ).use {
            setDescription(it)
        }
    }

    private fun setDescription(typedArray: TypedArray) {
        val description = typedArray.getString(chat.progressive.lib.ui.styles.R.styleable.SessionWarningInfoView_sessionsWarningInfoDescription)
        val hasLearnMore = typedArray.getBoolean(chat.progressive.lib.ui.styles.R.styleable.SessionWarningInfoView_sessionsWarningInfoHasLearnMore, false)
        if (hasLearnMore) {
            val learnMore = context.getString(CommonStrings.action_learn_more)
            val fullDescription = buildString {
                append(description)
                append(" ")
                append(learnMore)
            }

            binding.sessionWarningInfoDescription.setTextWithColoredPart(
                    fullText = fullDescription,
                    coloredPart = learnMore,
                    underline = false
            ) {
                onLearnMoreClickListener?.invoke()
            }
        } else {
            binding.sessionWarningInfoDescription.text = description
        }
    }
}
