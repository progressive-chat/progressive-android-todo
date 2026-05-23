#pragma once
#include <string>
#include <cstdint>

std::string parseWidgetEvent(const std::string& json);
std::string buildWidgetRequest(const std::string& json);
std::string validateWidgetUrl(const std::string& json);
std::string parseWidgetApiVersion(const std::string& json);
std::string formatWidgetHtml(const std::string& json);
