#pragma once
#include <string>
#include <cstdint>

std::string DraftType draftTypeFromString(const std(const std::string& json);
std::string string& s);(const std::string& json);
std::string content;             // Draft text/content(const std::string& json);
std::string linkedEventId;       // For Quote/Edit/Reply — target event(const std::string& json);
std::string roomId;(const std::string& json);
std::string draftPrefix = "draft(const std::string& json);
std::string "; // Prefix for auto-saved drafts(const std::string& json);
std::string void saveDraft(const std(const std::string& json);
std::string string& roomId, const UserDraft& draft);(const std::string& json);
std::string void deleteDraft(const std(const std::string& json);
std::string string& roomId);(const std::string& json);
std::string bool getDraft(const std(const std::string& json);
std::string string& roomId, UserDraft& out) const;(const std::string& json);
std::string bool hasDraft(const std(const std::string& json);
std::string string& roomId) const;(const std::string& json);
std::string bool qualifiesForAutoSave(const std(const std::string& json);
std::string string& text) const;(const std::string& json);
std::string bool autoSaveIfQualified(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& text);(const std::string& json);
std::string stripDraftPrefix(const std(const std::string& json);
std::string string& text) const;(const std::string& json);
std::string static UserDraft buildRegular(const std(const std::string& json);
std::string string& content);(const std::string& json);
std::string static UserDraft buildQuote(const std(const std::string& json);
std::string string& linkedEventId, const std(const std::string& json);
std::string string& content);(const std::string& json);
std::string static UserDraft buildEdit(const std(const std::string& json);
std::string string& linkedEventId, const std(const std::string& json);
std::string string& content);(const std::string& json);
std::string static UserDraft buildReply(const std(const std::string& json);
std::string string& linkedEventId, const std(const std::string& json);
std::string string& content);(const std::string& json);
std::string static UserDraft buildVoice(const std(const std::string& json);
std::string string& content);(const std::string& json);
std::string bool isContentTooLong(const std(const std::string& json);
std::string string& content) const;(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> getRoomsWithDrafts() const;(const std::string& json);
std::string draftToJson(const UserDraft& draft) const;(const std::string& json);
std::string configToJson() const;(const std::string& json);
std::string std(const std::string& json);
std::string unordered_map<std(const std::string& json);
std::string string, UserDraft> drafts_; // roomId → draft(const std::string& json);
