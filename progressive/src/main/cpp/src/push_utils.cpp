#include "progressive/push_utils.hpp"
#include <sstream>

namespace progressive {

std::vector<PushRule> parsePushRules(const std::string& json) {
    std::vector<PushRule> rules;
    size_t pos = 0;
    while (pos < json.size()) {
        auto rulePos = json.find("\"rule_id\":\"", pos);
        if (rulePos == std::string::npos) break;
        rulePos += 11;
        auto ruleEnd = json.find('"', rulePos);
        if (ruleEnd == std::string::npos) break;
        
        PushRule r;
        r.ruleId = json.substr(rulePos, ruleEnd - rulePos);
        rules.push_back(r);
        pos = ruleEnd + 1;
    }
    return rules;
}

std::string buildPushRuleContent(const std::string& pattern, const std::string& action,
                                   bool highlight, const std::string& sound) {
    std::ostringstream os;
    os << R"({"actions":[")" << action << R"("])";
    if (highlight) os << R"(,{"set_tweak":"highlight","value":true})";
    if (!sound.empty()) os << R"(,{"set_tweak":"sound","value":")" << sound << R"("})";
    os << R"(,"pattern":")" << pattern << R"(")";
    os << "}";
    return os.str();
}

bool matchesPushRule(const PushRule& rule, const std::string& eventContent,
                       const std::string& senderId, const std::string& roomId) {
    if (rule.kind == "room" && eventContent.find(rule.pattern) != std::string::npos) return true;
    if (rule.kind == "sender" && senderId == rule.pattern) return true;
    if (rule.kind == "content" && eventContent.find(rule.pattern) != std::string::npos) return true;
    return false;
}

std::string getDefaultPushAction(bool isDirect, bool isMuted, bool hasHighlight) {
    if (isMuted) return "dont_notify";
    if (hasHighlight) return "notify";
    if (isDirect) return "notify";
    return "dont_notify";
}

} // namespace progressive
