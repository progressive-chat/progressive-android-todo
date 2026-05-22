#pragma once
#include <string>
#include <vector>

namespace progressive {

struct RoomMemberCount {
    int joined = 0;
    int invited = 0;
    int left = 0;
    int banned = 0;
    int total() const { return joined + invited; }
};

// Parse member count from room summary
RoomMemberCount parseMemberCount(const std::string& summaryJson);

// Format member count for display ("5 members", "1 member", "0 members")
std::string formatMemberCount(int count);

// Format member count with online status ("5 members, 2 online")
std::string formatMemberCountWithOnline(int total, int online);

// Format membership event text
std::string formatMembershipEvent(const std::string& membership, const std::string& displayName,
                                    const std::string& reason = "");

// Get membership display string
std::string membershipToString(const std::string& membership);

} // namespace progressive
