#include "progressive/read_marker_utils.hpp"
#include <sstream>

namespace progressive {

std::string buildFullyReadMarker(const std::string& eventId) {
    return R"({"m.fully_read":")" + eventId + R"("})";
}

std::string buildReadReceipt(const std::string& eventId) {
    return R"({"m.read":{"data":{"event_id":")" + eventId + R"("}}})";
}

std::string parseReadMarkerEventId(const std::string& json) {
    auto fullyRead = json.find("\"m.fully_read\":\"");
    if (fullyRead == std::string::npos) {
        auto readPos = json.find("\"event_id\":\"");
        if (readPos == std::string::npos) return "";
        readPos += 12;
        auto end = json.find('"', readPos);
        return end != std::string::npos ? json.substr(readPos, end - readPos) : "";
    }
    fullyRead += 15;
    auto end = json.find('"', fullyRead);
    return end != std::string::npos ? json.substr(fullyRead, end - fullyRead) : "";
}

bool shouldShowReadMarker(const std::string& lastReadEvent, const std::string& currentEvent,
                           int lastReadIdx, int currentIdx) {
    return lastReadEvent == currentEvent || lastReadIdx == currentIdx;
}

std::string formatReadMarkerAccessibility(int unreadCount) {
    if (unreadCount <= 0) return "All read";
    return std::to_string(unreadCount) + " unread message" + (unreadCount == 1 ? "" : "s");
}

int compareEventIds(const std::string& a, const std::string& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

} // namespace progressive
