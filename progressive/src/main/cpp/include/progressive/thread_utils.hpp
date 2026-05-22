#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

struct ThreadInfo {
    std::string threadId;       // root event ID
    std::string roomId;
    std::string latestEventId;
    int replyCount = 0;
    int participantCount = 0;
    int64_t latestEventTs = 0;
    bool isUnread = false;
    int notificationCount = 0;
};

struct ThreadEvent {
    std::string eventId;
    std::string threadId;       // root event ID (m.relates_to.event_id)
    std::string relationType;   // "m.thread" or "m.annotation"
    bool isThreadRoot = false;
    bool isFallingBack = false; // rendered in main timeline too
};

// Parse m.thread relation from event content
ThreadEvent parseThreadRelation(const std::string& eventJson);

// Check if event is part of a thread
bool isInThread(const std::string& eventJson);

// Build m.relates_to for thread reply
std::string buildThreadRelation(const std::string& threadRootEventId, bool isFallingBack = false);

// Build thread root event content (for thread creation)
std::string buildThreadRootContent(const std::string& body, const std::string& formattedBody);

// Format thread info for UI display
std::string formatThreadSummary(const ThreadInfo& info);

} // namespace progressive
