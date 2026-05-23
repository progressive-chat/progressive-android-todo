#pragma once
#include <string>
#include <vector>
namespace progressive {
struct CustomEmoji { std::string shortcode; std::string mxcUrl; std::string label; };
std::string buildCustomEmojiImage(const CustomEmoji& emoji, int size=24);
std::string extractEmojiShortcode(const std::string& text);
std::string replaceEmojiShortcodes(const std::string& text, const std::vector<CustomEmoji>& emojis);
}
