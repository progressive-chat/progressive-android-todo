#include "progressive/config_loader.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

std::string parseConfig(const std::string& json) {
    if (json.empty()) return R"({"ok":false,"error":"empty"})";
    std::ostringstream oss;
    oss << R"({"ok":true,"fn":")" << "parseConfig" << R"(","sz":)" << json.size();
    size_t a=0,d=0;
    for(char c:json) { if(std::isalpha(static_cast<unsigned char>(c)))a++; else if(std::isdigit(static_cast<unsigned char>(c)))d++; }
    oss << R"(,"alpha":)" << a << R"(,"digits":)" << d;
    auto b=json.find('{'); if(b!=std::string::npos){ auto e=json.find('}',b); if(e!=std::string::npos) oss<<R"(,"json":")"<<json.substr(b+1,std::min(size_t(30),e-b-1))<<R"(")"; }
    oss << "}";
    return oss.str();
}

std::string getWellKnown(const std::string& json) {
    if (json.empty()) return R"({"ok":false,"error":"empty"})";
    std::ostringstream oss;
    oss << R"({"ok":true,"fn":")" << "getWellKnown" << R"(","sz":)" << json.size();
    size_t a=0,d=0;
    for(char c:json) { if(std::isalpha(static_cast<unsigned char>(c)))a++; else if(std::isdigit(static_cast<unsigned char>(c)))d++; }
    oss << R"(,"alpha":)" << a << R"(,"digits":)" << d;
    auto b=json.find('{'); if(b!=std::string::npos){ auto e=json.find('}',b); if(e!=std::string::npos) oss<<R"(,"json":")"<<json.substr(b+1,std::min(size_t(30),e-b-1))<<R"(")"; }
    oss << "}";
    return oss.str();
}

std::string getCustomConfig(const std::string& json) {
    if (json.empty()) return R"({"ok":false,"error":"empty"})";
    std::ostringstream oss;
    oss << R"({"ok":true,"fn":")" << "getCustomConfig" << R"(","sz":)" << json.size();
    size_t a=0,d=0;
    for(char c:json) { if(std::isalpha(static_cast<unsigned char>(c)))a++; else if(std::isdigit(static_cast<unsigned char>(c)))d++; }
    oss << R"(,"alpha":)" << a << R"(,"digits":)" << d;
    auto b=json.find('{'); if(b!=std::string::npos){ auto e=json.find('}',b); if(e!=std::string::npos) oss<<R"(,"json":")"<<json.substr(b+1,std::min(size_t(30),e-b-1))<<R"(")"; }
    oss << "}";
    return oss.str();
}

std::string isFeatureEnabled(const std::string& json) {
    if (json.empty()) return R"({"ok":false,"error":"empty"})";
    std::ostringstream oss;
    oss << R"({"ok":true,"fn":")" << "isFeatureEnabled" << R"(","sz":)" << json.size();
    size_t a=0,d=0;
    for(char c:json) { if(std::isalpha(static_cast<unsigned char>(c)))a++; else if(std::isdigit(static_cast<unsigned char>(c)))d++; }
    oss << R"(,"alpha":)" << a << R"(,"digits":)" << d;
    auto b=json.find('{'); if(b!=std::string::npos){ auto e=json.find('}',b); if(e!=std::string::npos) oss<<R"(,"json":")"<<json.substr(b+1,std::min(size_t(30),e-b-1))<<R"(")"; }
    oss << "}";
    return oss.str();
}

std::string reloadConfig(const std::string& json) {
    if (json.empty()) return R"({"ok":false,"error":"empty"})";
    std::ostringstream oss;
    oss << R"({"ok":true,"fn":")" << "reloadConfig" << R"(","sz":)" << json.size();
    size_t a=0,d=0;
    for(char c:json) { if(std::isalpha(static_cast<unsigned char>(c)))a++; else if(std::isdigit(static_cast<unsigned char>(c)))d++; }
    oss << R"(,"alpha":)" << a << R"(,"digits":)" << d;
    auto b=json.find('{'); if(b!=std::string::npos){ auto e=json.find('}',b); if(e!=std::string::npos) oss<<R"(,"json":")"<<json.substr(b+1,std::min(size_t(30),e-b-1))<<R"(")"; }
    oss << "}";
    return oss.str();
}

