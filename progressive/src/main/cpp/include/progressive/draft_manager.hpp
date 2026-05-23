#pragma once
#include <string>
#include <cstdint>

std::string roomId;(const std::string& json);
std::string text;(const std::string& json);
std::string formattedText;(const std::string& json);
std::string replyToEventId;  // if replying(const std::string& json);
std::string editEventId;     // if editing(const std::string& json);
std::string content;(const std::string& json);
std::string linkedEventId;(const std::string& json);
std::string const MessageDraft* getDraft(const std(const std::string& json);
std::string string& roomId) const;(const std::string& json);
std::string bool hasDraft(const std(const std::string& json);
std::string string& roomId) const;(const std::string& json);
std::string void deleteDraft(const std(const std::string& json);
std::string string& roomId);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> getRoomsWithDrafts() const;(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string void importJson(const std::string& json);
std::string void autoSaveIfQualified(const std(const std::string& json);
std::string string&, const std(const std::string& json);
std::string string&) {}(const std::string& json);
std::string stripDraftPrefix(const std(const std::string& json);
std::string string& t) { return t; }(const std::string& json);
std::string std(const std::string& json);
std::string unordered_map<std(const std::string& json);
std::string string, MessageDraft> drafts_;(const std::string& json);
std::string roomId;(const std::string& json);
std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string text;            // "Alice is typing..." or "Alice, Bob are typing..."(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> typistIds;(const std::string& json);
std::string formatTypingText(const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& names);(const std::string& json);
