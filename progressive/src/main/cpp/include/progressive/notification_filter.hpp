#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace progressive {

struct NotifFilterConfig {
    bool filterOutdated = true;       // skip events older than N seconds
    int maxAgeSeconds = 3600;         // 1 hour
    bool filterOwnMessages = true;   // skip own messages
    bool filterMutedRooms = true;    // skip muted rooms
    bool filterBotMessages = false;  // optionally skip bot messages
    std::unordered_set<std::string> hiddenSenderIds;
    std::unordered_set<std::string> hiddenRoomIds;
};

struct NotifFilterResult {
    bool shouldNotify = true;
    std::string reason;              // why it was filtered out (if not notifying)
};

// Check if a notification should be shown given the filter config
NotifFilterResult filterNotification(const std::string& eventJson,
                                      const std::string& senderId,
                                      const std::string& roomId,
                                      const std::string& myUserId,
                                      bool isRoomMuted,
                                      int64_t nowMs,
                                      const NotifFilterConfig& config);

// Check if event is outdated (too old for notification)
bool isOutdatedEvent(int64_t eventTs, int64_t nowMs, int maxAgeSeconds);

// Check if sender is the current user
bool isOwnMessage(const std::string& senderId, const std::string& myUserId);

// Format notification ticker text (status bar)
std::string formatTickerText(const std::string& senderName, const std::string& body);

// Get notification channel importance
std::string getNotificationChannel(const std::string& roomId, bool isHighlight, bool isDirect);

} // namespace progressive
