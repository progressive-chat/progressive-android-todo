#include "progressive/reply_utils.hpp"
#include <sstream>

namespace progressive {

std::string buildReplyRelation(const std::string& eventId) {
    std::ostringstream os;
    os << R"("m.relates_to":{"m.in_reply_to":{"event_id":")" << eventId << R"("}})";
    return os.str();
}

std::string formatReplyBody(const std::string& originalBody, const std::string& newBody) {
    std::ostringstream os;
    // Add "> " prefix to each line of original body
    std::istringstream iss(originalBody);
    std::string line;
    while (std::getline(iss, line)) os << "> " << line << "\n";
    os << "\n" << newBody;
    return os.str();
}

std::string formatReplyHtml(const ReplyInfo& info, const std::string& newBody,
                              const std::string& newFormattedBody) {
    std::ostringstream os;
    os << "<mx-reply>";
    os << "<blockquote>";
    os << "<a href=\"https://matrix.to/#/" << info.senderId << "\">" << info.senderName << "</a><br/>";
    os << info.formattedBody;
    os << "</blockquote>";
    os << "</mx-reply>";
    if (!newFormattedBody.empty()) os << newFormattedBody;
    else os << newBody;
    return os.str();
}

static std::string extractField(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":\"");
    if (p == std::string::npos) return "";
    p += key.size() + 4;
    auto e = json.find('"', p);
    if (e == std::string::npos) return "";
    return json.substr(p, e - p);
}

ReplyInfo parseReplyInfo(const std::string& json) {
    ReplyInfo info;
    auto relatesPos = json.find("\"m.in_reply_to\"");
    if (relatesPos != std::string::npos)
        info.eventId = extractField(json.substr(relatesPos), "event_id");
    return info;
}

bool isReplyEvent(const std::string& json) {
    return json.find("\"m.in_reply_to\"") != std::string::npos;
}

std::string extractReplyEventId(const std::string& json) {
    auto relatesPos = json.find("\"m.in_reply_to\"");
    if (relatesPos == std::string::npos) return "";
    return extractField(json.substr(relatesPos), "event_id");
}

} // namespace progressive
