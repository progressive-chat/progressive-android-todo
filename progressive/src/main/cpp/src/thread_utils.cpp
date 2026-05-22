#include "progressive/thread_utils.hpp"
#include <sstream>

namespace progressive {

static std::string extractField(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":\"");
    if (p == std::string::npos) {
        p = json.find("\"" + key + "\": \"");
        if (p == std::string::npos) return "";
        p += key.size() + 4;
    } else {
        p += key.size() + 4;
    }
    auto e = json.find('"', p);
    if (e == std::string::npos) return "";
    return json.substr(p, e - p);
}

ThreadEvent parseThreadRelation(const std::string& json) {
    ThreadEvent ev;
    auto relPos = json.find("\"m.relates_to\"");
    if (relPos == std::string::npos) return ev;
    
    ev.relationType = extractField(json, "rel_type");
    ev.threadId = extractField(json, "event_id");
    ev.isThreadRoot = json.find("\"m.thread\"") != std::string::npos &&
                      json.find("\"is_falling_back\"") == std::string::npos;
    
    // Check is_falling_back
    auto fbPos = json.find("\"is_falling_back\"");
    if (fbPos != std::string::npos) {
        ev.isFallingBack = json.find("true", fbPos) != std::string::npos;
    }
    
    return ev;
}

bool isInThread(const std::string& json) {
    auto relPos = json.find("\"m.relates_to\"");
    if (relPos == std::string::npos) return false;
    auto typePos = json.find("\"rel_type\"", relPos);
    if (typePos == std::string::npos) return false;
    return json.find("\"m.thread\"", typePos) != std::string::npos;
}

std::string buildThreadRelation(const std::string& threadRootEventId, bool isFallingBack) {
    std::ostringstream os;
    os << R"("m.relates_to":{)";
    os << R"("rel_type":"m.thread",)";
    os << R"("event_id":")" << threadRootEventId << R"(")";
    if (isFallingBack) os << R"(,"is_falling_back":true)";
    os << "}";
    return os.str();
}

std::string buildThreadRootContent(const std::string& body, const std::string& formattedBody) {
    std::ostringstream os;
    os << "{";
    os << R"("msgtype":"m.text",)";
    os << R"("body":")" << body << R"(")";
    if (!formattedBody.empty()) os << R"(,"formatted_body":")" << formattedBody << R"(")";
    os << R"(,"m.relates_to":{"rel_type":"m.thread","event_id":"$thread"))
       << R"(,"is_falling_back":true})";
    os << "}";
    return os.str();
}

std::string formatThreadSummary(const ThreadInfo& info) {
    std::ostringstream os;
    os << info.replyCount << " repl" << (info.replyCount == 1 ? "y" : "ies");
    os << " from " << info.participantCount << " participant" << (info.participantCount == 1 ? "" : "s");
    if (info.isUnread) os << " • Unread";
    return os.str();
}

} // namespace progressive
