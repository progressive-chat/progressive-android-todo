#pragma once
#include <string>
#include <vector>

namespace progressive {

struct RoomDirectoryEntry {
    std::string roomId;
    std::string name;
    std::string topic;
    std::string alias;
    std::string avatarUrl;
    int memberCount = 0;
    bool isPublic = true;
    bool isJoined = false;
};

// Parse directory entry from /publicRooms response
RoomDirectoryEntry parseDirectoryEntry(const std::string& json);

// Build room directory filter
std::string buildDirectoryFilter(const std::string& searchTerm, int limit = 20,
                                   const std::string& server = "");

// Parse directory list response
std::vector<RoomDirectoryEntry> parseDirectoryList(const std::string& json);

// Format directory entry for display
std::string formatDirectoryEntry(const RoomDirectoryEntry& entry);

} // namespace progressive
