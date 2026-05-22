#pragma once
#include <string>

namespace progressive {

struct UserProfile {
    std::string userId;
    std::string displayName;
    std::string avatarUrl;
    bool isDefault = false;
};

// Build profile fetch request (empty for GET)
std::string buildProfileRequest();

// Parse profile response from /profile API
UserProfile parseProfile(const std::string& json, const std::string& userId);

// Build profile update content
std::string buildProfileUpdate(const UserProfile& profile);

// Build display name change event content
std::string buildDisplayNameChange(const std::string& newName);

// Build avatar change event content
std::string buildAvatarUrlChange(const std::string& mxcUrl);

// Format profile for display summary
std::string formatProfileSummary(const UserProfile& profile);

} // namespace progressive
