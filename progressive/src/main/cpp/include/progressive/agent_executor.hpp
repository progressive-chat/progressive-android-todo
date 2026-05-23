#pragma once
#include <string>
#include <cstdint>

std::string systemPrompt;      // LLM system prompt (role + tools + rules)(const std::string& json);
std::string toolsDescription;  // JSON Schema of available tools(const std::string& json);
std::string toolName;          // "read_messages", "send_message", etc.(const std::string& json);
std::string argumentsJson;     // JSON object with tool parameters(const std::string& json);
std::string callId;            // unique ID for this call(const std::string& json);
std::string task;              // user's task description(const std::string& json);
std::string roomId;            // current room(const std::string& json);
std::string userId;            // requesting user(const std::string& json);
std::string roomContext;       // recent messages + room info(const std::string& json);
std::string llmResponse;       // latest raw LLM response(const std::string& json);
std::string finalAnswer;       // final text answer for the user(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> conversationHistory; // all prompts + responses(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string buildAgentSystemPrompt(const AgentConfig& config);(const std::string& json);
std::string buildAgentUserPrompt(const AgentState& state, const AgentConfig& config);(const std::string& json);
std::string formatMessagesForAgent((const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& senders,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& bodies,(const std::string& json);
std::string std(const std::string& json);
std::string vector<AgentToolCall> parseToolCalls(const std(const std::string& json);
std::string string& llmResponse);(const std::string& json);
std::string bool hasToolCalls(const std(const std::string& json);
std::string string& llmResponse);(const std::string& json);
std::string extractTextAnswer(const std(const std::string& json);
std::string string& llmResponse);(const std::string& json);
std::string AgentState processAgentIteration(const AgentState& state, const std(const std::string& json);
std::string string& llmRawResponse);(const std::string& json);
std::string buildToolResultText(const std(const std::string& json);
std::string string& toolName, const std(const std::string& json);
std::string string& resultJson);(const std::string& json);
std::string getAgentToolsSchema();(const std::string& json);
std::string agentStateToJson(const AgentState& state);(const std::string& json);
