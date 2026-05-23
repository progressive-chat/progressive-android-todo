#pragma once
#include <string>
#include <cstdint>

std::string name;          // e.g. "messagecontextmenu"(const std::string& json);
std::string soPath;        // e.g. "/data/app/.../libmessagecontextmenu.so"(const std::string& json);
std::string version;(const std::string& json);
std::string void scanDirectory(const std(const std::string& json);
std::string string& dirPath);(const std::string& json);
std::string void enable(const std(const std::string& json);
std::string string& name);(const std::string& json);
std::string void disable(const std(const std::string& json);
std::string string& name);(const std::string& json);
std::string bool isEnabled(const std(const std::string& json);
std::string string& name) const;(const std::string& json);
std::string const ModuleInfo* getModule(const std(const std::string& json);
std::string string& name) const;(const std::string& json);
std::string listModulesJson() const;(const std::string& json);
std::string std(const std::string& json);
std::string unordered_map<std(const std::string& json);
std::string string, ModuleInfo> modules_;(const std::string& json);
std::string bool validateModule(const std(const std::string& json);
std::string string& path) const;(const std::string& json);
std::string extractModuleVersion(const std(const std::string& json);
std::string string& soPath);(const std::string& json);
std::string bool isProgressiveModule(const std(const std::string& json);
std::string string& soPath);(const std::string& json);
