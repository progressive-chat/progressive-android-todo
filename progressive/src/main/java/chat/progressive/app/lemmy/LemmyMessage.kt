package chat.progressive.app.lemmy

import chat.progressive.app.protocol.*

data class LemmyMessage(
    override val id: Long,
    override val chatId: Long,
    override val senderId: String,
    override val senderName: String,
    override val text: String,
    override val timestamp: Long,
    override val isOutgoing: Boolean,
    override val contentType: ProtocolContentType = ProtocolContentType.TEXT,
    override val protocolType: ProtocolType = ProtocolType.LEMMY
) : IProtocolMessage
