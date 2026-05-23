#pragma once
#include <string>
#include <cstdint>

std::string RoomDirectoryVisibility visibilityFromString(const std(const std::string& json);
std::string string& s);(const std::string& json);
std::string alias;(const std::string& json);
std::string error;(const std::string& json);
std::string buildPublicRoomsRequest(const PublicRoomsParams& params) const;(const std::string& json);
std::string PublicRoomsResponse parsePublicRoomsResponse(const std(const std::string& json);
std::string string& json) const;(const std::string& json);
std::string buildVisibilityRequest(RoomDirectoryVisibility visibility) const;(const std::string& json);
std::string RoomDirectoryVisibility parseVisibilityResponse(const std(const std::string& json);
std::string string& json) const;(const std::string& json);
std::string buildAliasCheckRequest(const std(const std::string& json);
std::string string& aliasLocalPart) const;(const std::string& json);
std::string AliasAvailabilityResult parseAliasAvailability(const std(const std::string& json);
std::string string& json, const std(const std::string& json);
std::string string& aliasLocalPart) const;(const std::string& json);
std::string formatRoomPreview(const PublicRoom& room) const;(const std::string& json);
std::string buildRoomJoinUrl(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& viaServer) const;(const std::string& json);
std::string buildRoomAvatarUrl(const std(const std::string& json);
std::string string& avatarUrl, const std(const std::string& json);
std::string string& homeServer) const;(const std::string& json);
std::string std(const std::string& json);
std::string vector<PublicRoom> filterRooms(const std(const std::string& json);
std::string vector<PublicRoom>& rooms, const std(const std::string& json);
std::string string& query) const;(const std::string& json);
std::string roomToJson(const PublicRoom& room) const;(const std::string& json);
std::string roomsToJson(const std(const std::string& json);
std::string vector<PublicRoom>& rooms) const;(const std::string& json);
std::string responseToJson(const PublicRoomsResponse& resp) const;(const std::string& json);
std::string aliasResultToJson(const AliasAvailabilityResult& result) const;(const std::string& json);
std::string static extractStr(const std(const std::string& json);
std::string string& json, const std(const std::string& json);
std::string string& key);(const std::string& json);
std::string static int64_t extractInt(const std(const std::string& json);
std::string string& json, const std(const std::string& json);
std::string string& key);(const std::string& json);
std::string static bool extractBool(const std(const std::string& json);
std::string string& json, const std(const std::string& json);
std::string string& key);(const std::string& json);
