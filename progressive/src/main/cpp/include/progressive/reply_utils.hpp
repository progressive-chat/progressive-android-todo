#pragma once
#include <string>

namespace progressive {

struct ReplyInfo {
    std::string eventId;        // event being replied to
    std::string body;           // original body
    std::string formattedBody;  // original formatted body
    std::string senderId;       // original sender
    std::string senderName;     // original sender display name
};

// Build m.in_reply_to relation content
std::string buildReplyRelation(const std::string& eventId);

// Format reply body (adds "> original body" prefix)
std::string formatReplyBody(const std::string& originalBody, const std::string& newBody);

// Format reply HTML (adds <mx-reply> block)
std::string formatReplyHtml(const ReplyInfo& info, const std::string& newBody,
                              const std::string& newFormattedBody);

// Parse reply info from event content
ReplyInfo parseReplyInfo(const std::string& eventJson);

// Check if event is a reply
bool isReplyEvent(const std::string& eventJson);

// Extract the replied-to event ID
std::string extractReplyEventId(const std::string& eventJson);

} // namespace progressive
