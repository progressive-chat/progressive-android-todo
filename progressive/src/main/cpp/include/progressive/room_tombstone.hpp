#pragma once
#include <string>
#include <optional>

namespace progressive {

struct TombstoneInfo {
    std::string body;           // "This room has been replaced"
    std::string replacementRoomId;
    std::string replacementServer; // server part of replacement room ID
    bool isValid = false;
};

struct RoomUpgradeInfo {
    std::string fromRoomId;
    std::string toRoomId;
    std::string newVersion;     // e.g. "10"
    bool isUpgraded = false;
};

// Parse m.room.tombstone state event
TombstoneInfo parseTombstone(const std::string& eventJson);

// Parse m.room.create predecessor field for upgrade info
RoomUpgradeInfo parseRoomUpgrade(const std::string& createEventJson, const std::string& roomId);

// Check if a room is tombstoned (should not send messages)
bool isRoomTombstoned(const std::string& tombstoneJson);

// Format tombstone message for display
std::string formatTombstoneMessage(const TombstoneInfo& info);

// Get the room version from m.room.create event
std::string extractRoomVersion(const std::string& createEventJson);

} // namespace progressive
