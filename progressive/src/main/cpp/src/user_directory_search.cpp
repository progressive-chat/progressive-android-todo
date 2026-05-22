#include "progressive/user_directory_search.hpp"
#include <sstream>
#include <algorithm>

namespace progressive {

std::string buildUserSearchRequest(const std::string& query, int limit) {
    std::ostringstream os;
    os << R"({"search_term":")" << query << R"(",)";
    os << R"("limit":)" << limit;
    os << "}";
    return os.str();
}

std::vector<UserSearchResult> parseUserSearchResponse(const std::string& json) {
    std::vector<UserSearchResult> results;
    
    size_t pos = 0;
    while (true) {
        auto userIdPos = json.find("\"user_id\":\"", pos);
        if (userIdPos == std::string::npos) break;
        userIdPos += 11;
        auto userIdEnd = json.find('"', userIdPos);
        if (userIdEnd == std::string::npos) break;
        
        UserSearchResult r;
        r.userId = json.substr(userIdPos, userIdEnd - userIdPos);
        
        // Extract display name
        auto dnPos = json.find("\"display_name\":\"", userIdEnd);
        if (dnPos != std::string::npos && dnPos - userIdEnd < 200) {
            dnPos += 16;
            auto dnEnd = json.find('"', dnPos);
            if (dnEnd != std::string::npos) r.displayName = json.substr(dnPos, dnEnd - dnPos);
        }
        
        // Extract avatar
        auto avPos = json.find("\"avatar_url\":\"", userIdEnd);
        if (avPos != std::string::npos && avPos - userIdEnd < 200) {
            avPos += 14;
            auto avEnd = json.find('"', avPos);
            if (avEnd != std::string::npos) r.avatarUrl = json.substr(avPos, avEnd - avPos);
        }
        
        results.push_back(r);
        pos = userIdEnd + 1;
    }
    
    return results;
}

static std::string toLower(const std::string& s) {
    std::string r; r.reserve(s.size());
    std::transform(s.begin(), s.end(), std::back_inserter(r), ::tolower);
    return r;
}

std::vector<UserSearchResult> rankUserSearch(const std::vector<UserSearchResult>& results,
                                                const std::string& query, int maxResults) {
    std::vector<UserSearchResult> ranked = results;
    std::string q = toLower(query);
    
    // Score: exact match > startsWith > contains
    auto score = [&](const UserSearchResult& r) -> double {
        std::string name = toLower(r.displayName);
        std::string uid = toLower(r.userId);
        if (name == q) return 1.0;
        if (name.find(q) == 0) return 0.8;
        if (name.find(q) != std::string::npos) return 0.5;
        if (uid.find(q) != std::string::npos) return 0.3;
        return 0.1;
    };
    
    std::sort(ranked.begin(), ranked.end(),
        [&](auto& a, auto& b) { return score(a) > score(b); });
    
    if ((int)ranked.size() > maxResults) ranked.resize(maxResults);
    return ranked;
}

std::string formatUserSearchResult(const UserSearchResult& r) {
    std::ostringstream os;
    os << (r.displayName.empty() ? r.userId : r.displayName);
    if (!r.displayName.empty()) os << " (" << r.userId << ")";
    return os.str();
}

} // namespace progressive
