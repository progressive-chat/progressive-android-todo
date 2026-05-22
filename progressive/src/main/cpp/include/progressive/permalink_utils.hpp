#pragma once
#include <string>

namespace progressive {

// Build Matrix permalink: https://matrix.to/#/<type>/<id>
std::string buildMatrixLink(const std::string& type, const std::string& id);

// Build room permalink
std::string buildRoomPermalink(const std::string& roomId, const std::string& viaServer = "");

// Build user permalink
std::string buildUserPermalink(const std::string& userId);

// Build event permalink
std::string buildEventPermalink(const std::string& roomId, const std::string& eventId,
                                  const std::string& viaServer = "");

// Parse permalink to extract type and ID
bool parsePermalink(const std::string& url, std::string& type, std::string& id);

// Check if URL is a Matrix permalink
bool isPermalink(const std::string& url);

// Format permalink for display in message
std::string formatPermalink(const std::string& url, const std::string& label);

} // namespace progressive
