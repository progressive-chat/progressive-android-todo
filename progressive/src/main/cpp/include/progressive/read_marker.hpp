#pragma once
#include <string>
#include <cstdint>

std::string roomId;(const std::string& json);
std::string lastReadEventId;(const std::string& json);
std::string firstUnreadEventId;(const std::string& json);
std::string ReadMarkerState computeReadMarker(const std(const std::string& json);
std::string string& lastReadEventId,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& loadedEventIds,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& loadedSenders,(const std::string& json);
std::string const std(const std::string& json);
std::string string& myUserId);(const std::string& json);
std::string formatUnreadJumpLabel(const ReadMarkerState& state);(const std::string& json);
std::string formatTimeAgoLabel(int64_t timestampMs, int64_t nowMs);(const std::string& json);
std::string formatJumpToUnreadLabel(const ReadMarkerState& state, int64_t nowMs);(const std::string& json);
std::string advanceReadMarker(const std(const std::string& json);
std::string string& currentRoomId, const std(const std::string& json);
std::string string& latestEventId);(const std::string& json);
std::string readMarkerToJson(const ReadMarkerState& state);(const std::string& json);
