#include "progressive/custom_emoji_utils.hpp"
#include <sstream>
namespace progressive {
std::string buildCustomEmojiImage(const CustomEmoji& e, int size) {
    std::ostringstream os;
    os << "<img data-mx-emotion=\"" << e.shortcode << "\" src=\"" << e.mxcUrl
       << "\" alt=\"" << e.shortcode << "\" title=\"" << e.label << "\" height=\"" << size << "\"/>";
    return os.str();
}
std::string extractEmojiShortcode(const std::string& text) {
    auto p1 = text.find(":"); if (p1 == std::string::npos) return "";
    auto p2 = text.find(":", p1+1); return p2 != std::string::npos ? text.substr(p1+1, p2-p1-1) : "";
}
std::string replaceEmojiShortcodes(const std::string& text, const std::vector<CustomEmoji>& emojis) {
    std::string r = text; for (auto& e : emojis) {
        auto p = r.find(":"+e.shortcode+":"); if (p != std::string::npos) r.replace(p, e.shortcode.size()+2, buildCustomEmojiImage(e));
    }
    return r;
}
}
