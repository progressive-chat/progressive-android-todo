#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

enum class RoomTag { FAVOURITE, LOW_PRIORITY, SERVER_NOTICE, NONE };

struct RoomTagInfo {
    std::string roomId;
    RoomTag tag = RoomTag::NONE;
    double order = 0.0;         // m.order value (for favourites)
};

// Parse room tag from m.tag event
RoomTag parseRoomTag(const std::string& tagName);
std::string roomTagToString(RoomTag tag);

// Build m.tag event content
std::string buildRoomTagContent(RoomTag tag, double order = 0.0);

// Build tag removal content (untag)
std::string buildRemoveTagContent(RoomTag tag);

// Parse m.tag state event
RoomTagInfo parseRoomTagEvent(const std::string& roomId, const std::string& eventJson);

// Check tag presence
bool isFavourite(const std::string& tagEventJson);
bool isLowPriority(const std::string& tagEventJson);
bool isServerNotice(const std::string& tagEventJson);

} // namespace progressive
