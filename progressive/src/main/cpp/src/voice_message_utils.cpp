#include "progressive/voice_message_utils.hpp"
#include <sstream>
#include <algorithm>

namespace progressive {

std::string buildVoiceMessageContent(const VoiceMessageInfo& info) {
    std::ostringstream os;
    os << "{";
    os << R"("msgtype":"m.audio",)";
    os << R"("body":"Voice message",)";
    os << R"("url":")" << info.mxcUrl << R"(",)";
    os << R"("info":{)";
    os << R"("duration":)" << info.durationMs;
    os << R"(,"mimetype":")" << info.mimeType << R"(")";
    os << "},";
    os << R"("org.matrix.msc3245.voice":{})";
    os << "}";
    return os.str();
}

VoiceMessageInfo parseVoiceMessage(const std::string& json) {
    VoiceMessageInfo info;
    auto urlPos = json.find("\"url\":\"");
    if (urlPos != std::string::npos) {
        urlPos += 7;
        auto urlEnd = json.find('"', urlPos);
        if (urlEnd != std::string::npos) info.mxcUrl = json.substr(urlPos, urlEnd - urlPos);
    }
    
    auto mimetypePos = json.find("\"mimetype\":\"");
    if (mimetypePos != std::string::npos) {
        mimetypePos += 12;
        auto mimeEnd = json.find('"', mimetypePos);
        if (mimeEnd != std::string::npos) info.mimeType = json.substr(mimetypePos, mimeEnd - mimetypePos);
    }
    
    auto durPos = json.find("\"duration\":");
    if (durPos != std::string::npos) {
        durPos += 11;
        try { info.durationMs = std::stoi(json.substr(durPos)); } catch(...) {}
    }
    
    parseWaveform(json, info.waveform, info.waveformCount);
    return info;
}

void parseWaveform(const std::string& json, int waveform[], int& count, int maxSamples) {
    count = 0;
    auto wfPos = json.find("\"waveform\"");
    if (wfPos == std::string::npos) return;
    auto arrStart = json.find('[', wfPos);
    auto arrEnd = json.find(']', arrStart);
    if (arrStart == std::string::npos || arrEnd == std::string::npos) return;
    
    std::string arr = json.substr(arrStart + 1, arrEnd - arrStart - 1);
    size_t pos = 0;
    while (pos < arr.size() && count < maxSamples) {
        while (pos < arr.size() && arr[pos] == ' ') pos++;
        auto comma = arr.find(',', pos);
        if (comma == std::string::npos) comma = arr.size();
        try { waveform[count] = std::stoi(arr.substr(pos, comma - pos)); } catch(...) { waveform[count] = 0; }
        count++;
        pos = comma + 1;
    }
}

std::string formatVoiceDuration(int ms) {
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    
    std::ostringstream os;
    os << minutes << ":";
    if (seconds < 10) os << "0";
    os << seconds;
    return os.str();
}

bool isVoiceMessage(const std::string& json) {
    return json.find("\"org.matrix.msc3245.voice\"") != std::string::npos ||
           json.find("\"m.audio\"") != std::string::npos;
}

std::string formatWaveformBars(const int wf[], int cnt, int maxH) {
    std::ostringstream os;
    for (int i = 0; i < cnt && i < 60; i++) {
        int h = (wf[i] * maxH) / 1024;
        if (h < 1) h = 1;
        for (int j = 0; j < h; j++) os << "▌";
        os << " ";
    }
    return os.str();
}

} // namespace progressive
