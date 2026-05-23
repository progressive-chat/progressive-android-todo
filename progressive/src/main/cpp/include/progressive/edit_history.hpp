#pragma once
#include <string>
#include <cstdint>

std::string editEventId;(const std::string& json);
std::string editorId;(const std::string& json);
std::string editorName;(const std::string& json);
std::string newBody;           // the edited body text(const std::string& json);
std::string previousBody;      // body before this edit(const std::string& json);
std::string originalEventId;(const std::string& json);
std::string originalBody;(const std::string& json);
std::string originalSenderId;(const std::string& json);
std::string originalSenderName;(const std::string& json);
std::string EditHistory parseEditHistory(const std(const std::string& json);
std::string string& originalEventId, const std(const std::string& json);
std::string string& originalBody,(const std::string& json);
std::string const std(const std::string& json);
std::string string& originalSenderId, const std(const std::string& json);
std::string string& originalSenderName,(const std::string& json);
std::string int64_t originalSentAtMs, const std(const std::string& json);
std::string string& annotationsJson);(const std::string& json);
std::string formatEditHistory(const EditHistory& history);(const std::string& json);
std::string formatEditEntry(const EditEntry& entry, int index);(const std::string& json);
std::string getCurrentBody(const EditHistory& history);(const std::string& json);
std::string getEditBadgeText(int editCount);(const std::string& json);
std::string getEditCountBadge(int editCount);(const std::string& json);
std::string computeEditDiffSummary(const std(const std::string& json);
std::string string& oldBody, const std(const std::string& json);
std::string string& newBody);(const std::string& json);
std::string formatEditSummary(const EditEntry& entry);(const std::string& json);
std::string formatExpandedEditList(const EditHistory& history);(const std::string& json);
