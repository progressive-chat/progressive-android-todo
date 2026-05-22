#include "progressive/room_tag_utils.hpp"
#include <sstream>

namespace progressive {

RoomTag parseRoomTag(const std::string& tagName) {
    if (tagName == "m.favourite" || tagName == "m.favorite") return RoomTag::FAVOURITE;
    if (tagName == "m.lowpriority") return RoomTag::LOW_PRIORITY;
    if (tagName == "m.server_notice") return RoomTag::SERVER_NOTICE;
    return RoomTag::NONE;
}

std::string roomTagToString(RoomTag tag) {
    switch (tag) {
        case RoomTag::FAVOURITE: return "m.favourite";
        case RoomTag::LOW_PRIORITY: return "m.lowpriority";
        case RoomTag::SERVER_NOTICE: return "m.server_notice";
        default: return "";
    }
}

std::string buildRoomTagContent(RoomTag tag, double order) {
    std::ostringstream os;
    os << R"({"tags":{"m.favourite":{}})";
    if (order > 0.0) os << R"(,"order":)" << order;
    os << "}";
    return os.str();
}

std::string buildRemoveTagContent(RoomTag tag) {
    std::ostringstream os;
    os << R"({"tags":{"m.favourite":{}})";
    return os.str();
}

RoomTagInfo parseRoomTagEvent(const std::string& roomId, const std::string& json) {
    RoomTagInfo info;
    info.roomId = roomId;
    
    if (json.find("\"m.favourite\"") != std::string::npos || json.find("\"m.favorite\"") != std::string::npos)
        info.tag = RoomTag::FAVOURITE;
    else if (json.find("\"m.lowpriority\"") != std::string::npos)
        info.tag = RoomTag::LOW_PRIORITY;
    else if (json.find("\"m.server_notice\"") != std::string::npos)
        info.tag = RoomTag::SERVER_NOTICE;
    
    auto orderPos = json.find("\"order\":");
    if (orderPos != std::string::npos) {
        orderPos += 8;
        try { info.order = std::stod(json.substr(orderPos)); } catch(...) {}
    }
    return info;
}

bool isFavourite(const std::string& json) { return json.find("\"m.favourite\"") != std::string::npos; }
bool isLowPriority(const std::string& json) { return json.find("\"m.lowpriority\"") != std::string::npos; }
bool isServerNotice(const std::string& json) { return json.find("\"m.server_notice\"") != std::string::npos; }

} // namespace progressive
