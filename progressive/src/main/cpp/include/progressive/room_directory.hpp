#pragma once
#include <string>
#include <cstdint>

std::string roomId;(const std::string& json);
std::string name;(const std::string& json);
std::string topic;(const std::string& json);
std::string alias;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string serverFilter;    // filter by server (empty = all)(const std::string& json);
std::string nameFilter;      // search by name (empty = all)(const std::string& json);
std::string biggestRoom;(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> availableServers;(const std::string& json);
std::string const std(const std::string& json);
std::string string& query, int maxResults = 20(const std::string& json);
std::string void sortRooms(std(const std::string& json);
std::string vector<RoomDirectoryEntry>& rooms, const std(const std::string& json);
std::string string& sortBy);(const std::string& json);
std::string formatDirectoryEntry(const RoomDirectoryEntry& entry);(const std::string& json);
std::string directoryStatsToJson(const DirectoryStats& stats);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> extractServers(const std(const std::string& json);
std::string vector<RoomDirectoryEntry>& rooms);(const std::string& json);
