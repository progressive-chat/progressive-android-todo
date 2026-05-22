#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

struct UserSearchResult {
    std::string userId;
    std::string displayName;
    std::string avatarUrl;
    double relevance = 0.0;
    int mutualRooms = 0;
};

// Build user directory search request body
std::string buildUserSearchRequest(const std::string& query, int limit = 20);

// Parse user directory search response
std::vector<UserSearchResult> parseUserSearchResponse(const std::string& json);

// Filter and rank results
std::vector<UserSearchResult> rankUserSearch(const std::vector<UserSearchResult>& results,
                                                const std::string& query,
                                                int maxResults = 10);

// Format user search result for display
std::string formatUserSearchResult(const UserSearchResult& result);

} // namespace progressive
