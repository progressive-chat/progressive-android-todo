#include "progressive/notification_filter.hpp"
#include <sstream>

namespace progressive {

bool isOutdatedEvent(int64_t eventTs, int64_t nowMs, int maxAgeSeconds) {
    return (nowMs - eventTs) > (maxAgeSeconds * 1000LL);
}

bool isOwnMessage(const std::string& senderId, const std::string& myUserId) {
    return senderId == myUserId;
}

NotifFilterResult filterNotification(const std::string& eventJson,
                                       const std::string& senderId,
                                       const std::string& roomId,
                                       const std::string& myUserId,
                                       bool isRoomMuted,
                                       int64_t nowMs,
                                       const NotifFilterConfig& config) {
    NotifFilterResult r;
    
    if (config.filterOwnMessages && isOwnMessage(senderId, myUserId)) {
        r.shouldNotify = false; r.reason = "own message"; return r;
    }
    if (config.filterMutedRooms && isRoomMuted) {
        r.shouldNotify = false; r.reason = "room muted"; return r;
    }
    if (config.hiddenSenderIds.count(senderId)) {
        r.shouldNotify = false; r.reason = "sender hidden"; return r;
    }
    if (config.hiddenRoomIds.count(roomId)) {
        r.shouldNotify = false; r.reason = "room hidden"; return r;
    }
    if (config.filterOutdated) {
        auto tsPos = eventJson.find("\"origin_server_ts\":");
        if (tsPos != std::string::npos) {
            tsPos += 18;
            try {
                int64_t ts = std::stoll(eventJson.substr(tsPos));
                if (isOutdatedEvent(ts, nowMs, config.maxAgeSeconds)) {
                    r.shouldNotify = false; r.reason = "outdated"; return r;
                }
            } catch(...) {}
        }
    }
    
    return r;
}

std::string formatTickerText(const std::string& senderName, const std::string& body) {
    return senderName + ": " + body;
}

std::string getNotificationChannel(const std::string& roomId, bool isHighlight, bool isDirect) {
    if (isHighlight) return "highlights";
    if (isDirect) return "direct_messages";
    return "messages";
}

} // namespace progressive
