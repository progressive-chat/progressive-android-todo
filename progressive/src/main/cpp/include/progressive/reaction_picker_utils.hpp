#pragma once
#include <string>
#include <vector>

namespace progressive {

struct ReactionCategory {
    std::string name;           // "Smileys", "Gestures", etc.
    std::vector<std::string> emojis;
};

// Get common emoji reactions
std::vector<std::string> getQuickReactions();

// Get emoji by category
std::vector<ReactionCategory> getEmojiCategories();

// Build m.reaction event content
std::string buildReactionContent(const std::string& eventId, const std::string& emoji);

// Parse reaction key (the emoji) from event
std::string parseReactionKey(const std::string& json);

// Check if event is a reaction
bool isReactionEvent(const std::string& json);

// Get emoji description for accessibility
std::string getEmojiDescription(const std::string& emoji);

} // namespace progressive
