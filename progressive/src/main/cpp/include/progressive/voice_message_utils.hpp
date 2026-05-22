#pragma once
#include <string>
#include <cstdint>

namespace progressive {

struct VoiceMessageInfo {
    std::string mxcUrl;
    std::string mimeType;       // "audio/ogg", "audio/mp4"
    int durationMs = 0;         // duration in milliseconds
    int waveform[120] = {};     // waveform samples (0-1024)
    int waveformCount = 0;
};

// Build m.audio info for voice message content
std::string buildVoiceMessageContent(const VoiceMessageInfo& info);

// Parse voice message info from event content
VoiceMessageInfo parseVoiceMessage(const std::string& json);

// Format duration for display ("1:23", "0:45")
std::string formatVoiceDuration(int durationMs);

// Parse waveform array from JSON
void parseWaveform(const std::string& json, int waveform[], int& count, int maxSamples = 120);

// Check if event is a voice message
bool isVoiceMessage(const std::string& json);

// Format waveform bars for UI display string
std::string formatWaveformBars(const int waveform[], int count, int maxHeight = 20);

} // namespace progressive
