#include "progressive/reaction_picker_utils.hpp"
#include <sstream>

namespace progressive {

std::vector<std::string> getQuickReactions() {
    return {"👍", "❤️", "😂", "😮", "😢", "👏", "🎉", "🔥", "💯", "✅"};
}

std::vector<ReactionCategory> getEmojiCategories() {
    return {
        {"Smileys", {"😀","😃","😄","😁","😅","🤣","😂","🙂","😊","😇"}},
        {"Gestures", {"👍","👎","👏","🙌","🤝","👋","✌️","🤞","💪","🙏"}},
        {"Hearts", {"❤️","🧡","💛","💚","💙","💜","🖤","🤍","🤎","💕"}},
        {"Objects", {"🎉","🎂","🔥","⭐","💯","✅","❌","⚡","🌟","🎵"}}
    };
}

std::string buildReactionContent(const std::string& eventId, const std::string& emoji) {
    std::ostringstream os;
    os << R"({"m.relates_to":{)";
    os << R"("event_id":")" << eventId << R"(",)";
    os << R"("key":")" << emoji << R"(",)";
    os << R"("rel_type":"m.annotation")";
    os << "}}";
    return os.str();
}

std::string parseReactionKey(const std::string& json) {
    auto keyPos = json.find("\"key\":\"");
    if (keyPos == std::string::npos) return "";
    keyPos += 7;
    auto end = json.find('"', keyPos);
    return end != std::string::npos ? json.substr(keyPos, end - keyPos) : "";
}

bool isReactionEvent(const std::string& json) {
    return json.find("\"rel_type\":\"m.annotation\"") != std::string::npos;
}

std::string getEmojiDescription(const std::string& e) {
    if (e == "👍") return "Thumbs up";
    if (e == "❤️") return "Heart";
    if (e == "😂") return "Laugh";
    if (e == "😮") return "Wow";
    if (e == "😢") return "Sad";
    if (e == "👏") return "Clap";
    if (e == "🎉") return "Party";
    if (e == "🔥") return "Fire";
    return e;
}

} // namespace progressive
