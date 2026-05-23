#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string void hideFor(const std(const std::string& json);
std::string string& userId, const std(const std::string& json);
std::string string& displayName, int minutes);(const std::string& json);
std::string bool isHidden(const std(const std::string& json);
std::string string& userId) const;(const std::string& json);
std::string int getRemainingSeconds(const std(const std::string& json);
std::string string& userId) const;(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string msgId;           // unique ID(const std::string& json);
std::string roomId;(const std::string& json);
std::string body;(const std::string& json);
std::string formattedBody;(const std::string& json);
std::string lastError;(const std::string& json);
std::string void setOrder(const std(const std::string& json);
std::string string& msgId, int order);(const std::string& json);
std::string void markFailed(const std(const std::string& json);
std::string string& msgId, const std(const std::string& json);
std::string string& error);(const std::string& json);
std::string void markSent(const std(const std::string& json);
std::string string& msgId);(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string sourcePath;(const std::string& json);
std::string outputPath;      // cropped PNG in zip(const std::string& json);
std::string roomId;(const std::string& json);
std::string eventId;(const std::string& json);
std::string userMembership;    // "join", "invite", "leave", "ban"(const std::string& json);
std::string label;(const std::string& json);
std::string icon;(const std::string& json);
std::string getToolLabel(ChatTool tool);(const std::string& json);
std::string getToolIcon(ChatTool tool);(const std::string& json);
std::string executeToolAction(ChatTool tool, const ChatToolContext& ctx);(const std::string& json);
std::string getToolDescription(ChatTool tool);(const std::string& json);
std::string buildShareContent(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& eventId, const std(const std::string& json);
std::string string& body);(const std::string& json);
std::string int getUserMembershipLevel(const std(const std::string& json);
std::string string& membership);(const std::string& json);
std::string contextToJson(const ChatToolContext& ctx);(const std::string& json);
