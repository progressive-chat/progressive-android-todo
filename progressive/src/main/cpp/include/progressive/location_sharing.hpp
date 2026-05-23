#pragma once
#include <string>
#include <cstdint>

std::string sessionId;(const std::string& json);
std::string roomId;         // target room(const std::string& json);
std::string userId;         // the sharer(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> participants;  // additional sharers(const std::string& json);
std::string startSession(const LocationSession& session);(const std::string& json);
std::string void stopSession(const std(const std::string& json);
std::string string& sessionId);(const std::string& json);
std::string std(const std::string& json);
std::string vector<LocationSession> getActiveSessions(const std(const std::string& json);
std::string string& userId) const;(const std::string& json);
std::string bool isDue(const std(const std::string& json);
std::string string& sessionId) const;(const std::string& json);
std::string void markSent(const std(const std::string& json);
std::string string& sessionId, const GeoCoord& coord);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> checkAutoStop();(const std::string& json);
std::string const LocationSession* getSession(const std(const std::string& json);
std::string string& sessionId) const;(const std::string& json);
std::string static formatLocationMessage(const GeoCoord& coord, const std(const std::string& json);
std::string string& label = "");(const std::string& json);
std::string static formatGeoUri(const GeoCoord& coord);(const std::string& json);
std::string static formatGeoJson(const GeoCoord& coord);(const std::string& json);
std::string static GeoCoord parseFromMessage(const std(const std::string& json);
std::string string& body);(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string generateId();(const std::string& json);
