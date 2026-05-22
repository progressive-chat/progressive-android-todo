#pragma once
#include <string>
#include <vector>

namespace progressive {

struct MessageFormatOptions {
    bool enableMarkdown = true;
    bool enableEmoji = true;
    bool enableMentions = true;
    bool enableLinks = true;
    int maxBodyLength = 4096;
};

// Format message body for display (apply markdown, highlight mentions, linkify URLs)
std::string formatMessageBody(const std::string& body, const std::string& formattedBody,
                               const std::string& myUserId,
                               const MessageFormatOptions& opts = {});

// Format notification body (stripped, short)
std::string formatNotificationBody(const std::string& body, int maxLen = 200);

// Format sender name for display (with power level colour if applicable)
std::string formatMessageSender(const std::string& displayName, const std::string& userId,
                                 int powerLevel = 0);

// Build mention pill HTML
std::string buildMentionPill(const std::string& userId, const std::string& displayName);

// Count emoji in text
int countEmoji(const std::string& text);
bool isOnlyEmoji(const std::string& text);

} // namespace progressive
