#pragma once
#include <string>
#include <cstdint>

namespace progressive {

// Build fully read marker event content
std::string buildFullyReadMarker(const std::string& eventId);
std::string buildReadReceipt(const std::string& eventId);

// Parse read marker event
std::string parseReadMarkerEventId(const std::string& json);

// Check if event should show read marker indicator
bool shouldShowReadMarker(const std::string& lastReadEventId, const std::string& currentEventId,
                           int lastReadIndex, int currentIndex);

// Format read marker text for accessibility
std::string formatReadMarkerAccessibility(int unreadCount);

// Compare event IDs for ordering (lexicographic)
int compareEventIds(const std::string& a, const std::string& b);

} // namespace progressive
