#pragma once
#include <string>
#include <cstdint>

std::string symbol;      // e.g. "→", "≈", "☭", "¯\_(ツ)_/¯"(const std::string& json);
std::string label;       // optional display label(const std::string& json);
std::string void addSymbol(const std(const std::string& json);
std::string string& symbol, const std(const std::string& json);
std::string string& label = "");(const std::string& json);
std::string void removeSymbol(const std(const std::string& json);
std::string string& symbol);(const std::string& json);
std::string void setOrder(const std(const std::string& json);
std::string string& symbol, int order);(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string void importJson(const std::string& json);
std::string std(const std::string& json);
std::string unordered_map<std(const std::string& json);
std::string string, SymbolEntry> symbols_;(const std::string& json);
std::string pattern;     // "www.youtube.com"(const std::string& json);
std::string replacement; // "redirect.invidious.io"(const std::string& json);
std::string void addRule(const std(const std::string& json);
std::string string& pattern, const std(const std::string& json);
std::string string& replacement, bool exactMatch = false);(const std::string& json);
std::string void removeRule(const std(const std::string& json);
std::string string& pattern);(const std::string& json);
std::string void setEnabled(const std(const std::string& json);
std::string string& pattern, bool enabled);(const std::string& json);
std::string apply(const std(const std::string& json);
std::string string& text) const;(const std::string& json);
std::string const ReplacementRule* check(const std(const std::string& json);
std::string string& text) const;(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string void importJson(const std::string& json);
std::string static toLower(const std(const std::string& json);
std::string string& s);(const std::string& json);
