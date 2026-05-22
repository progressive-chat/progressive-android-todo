#include "progressive/message_format_helper.hpp"
#include <sstream>

namespace progressive {

std::string formatMessageBody(const std::string& body, const std::string& formattedBody,
                                const std::string& myUserId, const MessageFormatOptions& opts) {
    if (!formattedBody.empty() && opts.enableMarkdown) return formattedBody;
    
    std::string result = body;
    if ((int)result.size() > opts.maxBodyLength) result = result.substr(0, opts.maxBodyLength);
    return result;
}

std::string formatNotificationBody(const std::string& body, int maxLen) {
    std::string result;
    bool inTag = false;
    for (char c : body) {
        if (c == '<') inTag = true;
        else if (c == '>') inTag = false;
        else if (!inTag) result += c;
    }
    if ((int)result.size() > maxLen) result = result.substr(0, maxLen - 3) + "...";
    return result;
}

std::string formatMessageSender(const std::string& displayName, const std::string& userId,
                                  int powerLevel) {
    std::ostringstream os;
    os << (displayName.empty() ? userId : displayName);
    if (powerLevel >= 100) os << " 👑";
    else if (powerLevel >= 50) os << " ⭐";
    return os.str();
}

std::string buildMentionPill(const std::string& userId, const std::string& displayName) {
    std::ostringstream os;
    os << "<a href=\"https://matrix.to/#/" << userId << "\">";
    os << (displayName.empty() ? userId : displayName);
    os << "</a>";
    return os.str();
}

int countEmoji(const std::string& text) {
    int count = 0;
    for (size_t i = 0; i < text.size(); i++) {
        unsigned char c = text[i];
        if (c >= 0xF0) { count++; i += 3; }       // 4-byte UTF-8
        else if (c == 0xE2 || c == 0xC2) {         // common emoji ranges
            if (i + 2 < text.size()) {
                unsigned char c2 = text[i+1];
                if ((c == 0xE2 && c2 >= 0x9C) || (c == 0xC2 && c2 == 0xA9)) { count++; i += 2; }
            }
        }
    }
    return count;
}

bool isOnlyEmoji(const std::string& text) {
    if (text.empty()) return false;
    int emoji = countEmoji(text);
    int spaces = 0;
    for (char c : text) if (c == ' ') spaces++;
    return emoji > 0 && (emoji + spaces) * 2 >= (int)text.size();
}

} // namespace progressive
