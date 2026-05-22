#include "progressive/room_tombstone.hpp"

namespace progressive {

static std::string extractField(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":\"");
    if (p == std::string::npos) return "";
    p += key.size() + 4;
    auto e = json.find('"', p);
    if (e == std::string::npos) return "";
    return json.substr(p, e - p);
}

TombstoneInfo parseTombstone(const std::string& json) {
    TombstoneInfo t;
    if (json.empty()) return t;
    
    t.body = extractField(json, "body");
    t.replacementRoomId = extractField(json, "replacement_room");
    t.isValid = !t.replacementRoomId.empty();
    
    auto colon = t.replacementRoomId.find(':');
    if (colon != std::string::npos) {
        t.replacementServer = t.replacementRoomId.substr(colon + 1);
    }
    
    return t;
}

RoomUpgradeInfo parseRoomUpgrade(const std::string& createEventJson, const std::string& roomId) {
    RoomUpgradeInfo u;
    u.fromRoomId = roomId;
    
    auto predPos = createEventJson.find("\"predecessor\"");
    if (predPos != std::string::npos) {
        u.toRoomId = extractField(createEventJson.substr(predPos), "room_id");
        u.isUpgraded = !u.toRoomId.empty();
    }
    u.newVersion = extractRoomVersion(createEventJson);
    
    return u;
}

bool isRoomTombstoned(const std::string& json) {
    if (json.empty()) return false;
    return json.find("\"replacement_room\":\"!") != std::string::npos;
}

std::string formatTombstoneMessage(const TombstoneInfo& info) {
    if (!info.isValid) return "This room has been replaced.";
    return "This room has been replaced. The conversation continues in the new room.";
}

std::string extractRoomVersion(const std::string& json) {
    auto v = extractField(json, "room_version");
    return v.empty() ? "1" : v;
}

} // namespace progressive
