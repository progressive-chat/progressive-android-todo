/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.attachments

import chat.progressive.lib.multipicker.entity.MultiPickerAudioType
import chat.progressive.lib.multipicker.entity.MultiPickerBaseMediaType
import chat.progressive.lib.multipicker.entity.MultiPickerBaseType
import chat.progressive.lib.multipicker.entity.MultiPickerContactType
import chat.progressive.lib.multipicker.entity.MultiPickerFileType
import chat.progressive.lib.multipicker.entity.MultiPickerImageType
import chat.progressive.lib.multipicker.entity.MultiPickerVideoType
import org.matrix.android.sdk.api.session.content.ContentAttachmentData
import org.matrix.android.sdk.api.util.MimeTypes.isMimeTypeAudio
import org.matrix.android.sdk.api.util.MimeTypes.isMimeTypeImage
import org.matrix.android.sdk.api.util.MimeTypes.isMimeTypeVideo
import timber.log.Timber

fun MultiPickerContactType.toContactAttachment(): ContactAttachment {
    return ContactAttachment(
            displayName = displayName,
            photoUri = photoUri,
            emails = emailList.toList(),
            phones = phoneNumberList.toList()
    )
}

fun MultiPickerFileType.toContentAttachmentData(): ContentAttachmentData {
    if (mimeType == null) Timber.w("No mimeType")
    return ContentAttachmentData(
            mimeType = mimeType,
            type = mapType(),
            size = size,
            name = displayName,
            queryUri = contentUri
    )
}

fun MultiPickerAudioType.toContentAttachmentData(isVoiceMessage: Boolean): ContentAttachmentData {
    if (mimeType == null) Timber.w("No mimeType")
    return ContentAttachmentData(
            mimeType = mimeType,
            type = if (isVoiceMessage) ContentAttachmentData.Type.VOICE_MESSAGE else mapType(),
            size = size,
            name = displayName,
            duration = duration,
            queryUri = contentUri,
            waveform = waveform
    )
}

private fun MultiPickerBaseType.mapType(): ContentAttachmentData.Type {
    return when {
        mimeType?.isMimeTypeImage() == true -> ContentAttachmentData.Type.IMAGE
        mimeType?.isMimeTypeVideo() == true -> ContentAttachmentData.Type.VIDEO
        mimeType?.isMimeTypeAudio() == true -> ContentAttachmentData.Type.AUDIO
        else -> ContentAttachmentData.Type.FILE
    }
}

fun MultiPickerBaseType.toContentAttachmentData(): ContentAttachmentData {
    return when (this) {
        is MultiPickerImageType -> toContentAttachmentData()
        is MultiPickerVideoType -> toContentAttachmentData()
        is MultiPickerAudioType -> toContentAttachmentData(isVoiceMessage = false)
        is MultiPickerFileType -> toContentAttachmentData()
        else -> throw IllegalStateException("Unknown file type")
    }
}

fun MultiPickerBaseMediaType.toContentAttachmentData(): ContentAttachmentData {
    return when (this) {
        is MultiPickerImageType -> toContentAttachmentData()
        is MultiPickerVideoType -> toContentAttachmentData()
        else -> throw IllegalStateException("Unknown media type")
    }
}

fun MultiPickerImageType.toContentAttachmentData(): ContentAttachmentData {
    if (mimeType == null) Timber.w("No mimeType")
    return ContentAttachmentData(
            mimeType = mimeType,
            type = mapType(),
            name = displayName,
            size = size,
            height = height.toLong(),
            width = width.toLong(),
            exifOrientation = orientation,
            queryUri = contentUri
    )
}

fun MultiPickerVideoType.toContentAttachmentData(): ContentAttachmentData {
    if (mimeType == null) Timber.w("No mimeType")
    return ContentAttachmentData(
            mimeType = mimeType,
            type = ContentAttachmentData.Type.VIDEO,
            size = size,
            height = height.toLong(),
            width = width.toLong(),
            duration = duration,
            name = displayName,
            queryUri = contentUri
    )
}
