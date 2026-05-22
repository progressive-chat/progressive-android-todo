#include "progressive/file_upload_utils.hpp"
#include <sstream>
#include <iomanip>

namespace progressive {

std::string buildFileUploadContent(const FileUploadInfo& info, const std::string& body) {
    std::ostringstream os;
    os << "{";
    os << R"("msgtype":"m.file",)";
    os << R"("body":")" << (body.empty() ? info.fileName : body) << R"(",)";
    os << R"("filename":")" << info.fileName << R"(",)";
    os << R"("url":")" << info.mxcUrl << R"(",)";
    os << R"("info":{)";
    os << R"("mimetype":")" << info.mimeType << R"(",)";
    os << R"("size":)" << info.fileSizeBytes;
    if (info.width > 0) os << R"(,"w":)" << info.width;
    if (info.height > 0) os << R"(,"h":)" << info.height;
    os << "}";
    os << "}";
    return os.str();
}

FileUploadInfo parseFileUpload(const std::string& json) {
    FileUploadInfo info;
    auto extract = [&](const std::string& key) -> std::string {
        auto p = json.find("\"" + key + "\":\"");
        if (p == std::string::npos) return "";
        p += key.size() + 4;
        auto e = json.find('"', p);
        if (e == std::string::npos) return "";
        return json.substr(p, e - p);
    };
    info.mxcUrl = extract("url");
    info.mimeType = extract("mimetype");
    info.fileName = extract("filename");
    return info;
}

std::string formatFileSize(int64_t bytes) {
    if (bytes < 1024) return std::to_string(bytes) + " B";
    double kb = bytes / 1024.0;
    if (kb < 1024) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << kb << " KB";
        return os.str();
    }
    double mb = kb / 1024.0;
    if (mb < 1024) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << mb << " MB";
        return os.str();
    }
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << mb / 1024.0 << " GB";
    return os.str();
}

std::string getFileExtension(const std::string& mime) {
    if (mime == "image/jpeg") return "jpg";
    if (mime == "image/png") return "png";
    if (mime == "image/gif") return "gif";
    if (mime == "video/mp4") return "mp4";
    if (mime == "audio/mp3") return "mp3";
    if (mime == "audio/ogg") return "ogg";
    if (mime == "application/pdf") return "pdf";
    return "bin";
}

std::string getFileIcon(const std::string& mime) {
    if (mime.find("image/") == 0) return "ic_file_image";
    if (mime.find("video/") == 0) return "ic_file_video";
    if (mime.find("audio/") == 0) return "ic_file_audio";
    if (mime == "application/pdf") return "ic_file_pdf";
    if (mime.find("text/") == 0) return "ic_file_text";
    return "ic_file_generic";
}

bool isFileImage(const std::string& mime) { return mime.find("image/") == 0; }

std::string buildThumbnailUrl(const std::string& mxcUrl, const std::string& homeserver,
                                int w, int h, const std::string& method) {
    if (mxcUrl.empty()) return "";
    const std::string prefix = "mxc://";
    if (mxcUrl.compare(0, prefix.size(), prefix) != 0) return mxcUrl;
    auto slash = mxcUrl.find('/', prefix.size());
    std::string server = mxcUrl.substr(prefix.size(), slash - prefix.size());
    std::string mediaId = mxcUrl.substr(slash + 1);
    std::string base = homeserver;
    while (!base.empty() && base.back() == '/') base.pop_back();
    std::ostringstream os;
    os << base << "/_matrix/media/v3/thumbnail/" << server << "/" << mediaId;
    os << "?width=" << w << "&height=" << h << "&method=" << method;
    return os.str();
}

} // namespace progressive
