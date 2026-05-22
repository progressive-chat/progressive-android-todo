/*
 * Copyright 2020-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.core.ui.views

import android.content.Context
import android.graphics.Color
import android.util.AttributeSet
import androidx.appcompat.widget.AppCompatImageView
import chat.progressive.app.core.qrcode.toBitMatrix
import chat.progressive.app.core.qrcode.toBitmap

class QrCodeImageView @JvmOverloads constructor(
        context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : AppCompatImageView(context, attrs, defStyleAttr) {

    private var data: String? = null

    init {
        setBackgroundColor(Color.WHITE)
    }

    fun setData(data: String) {
        this.data = data

        render()
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        render()
    }

    private fun render() {
        data
                ?.takeIf { height > 0 }
                ?.let {
                    val bitmap = it.toBitMatrix(height).toBitmap()
                    post { setImageBitmap(bitmap) }
                }
    }
}
