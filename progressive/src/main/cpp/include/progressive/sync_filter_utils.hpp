#pragma once
#include <string>
#include <vector>

namespace progressive {

// Build room event filter (types to include/exclude)
std::string buildRoomEventFilter(const std::vector<std::string>& types, bool include);

// Build sync filter with lazy loading
std::string buildSyncFilter(int timelineLimit = 20, bool lazyLoadMembers = true);

// Build filter for specific rooms
std::string buildRoomFilter(const std::vector<std::string>& roomIds, bool include);

} // namespace progressive
