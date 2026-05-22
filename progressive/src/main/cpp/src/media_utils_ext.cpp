#include "progressive/media_utils_ext.hpp"
#include <sstream>
#include <utility>

namespace progressive {

std::string buildDownloadUrl(const std::string& mxcUrl, const std::string& homeserver) {
    const std::string prefix = "mxc://";
    if (mxcUrl.compare(0, prefix.size(), prefix) != 0) return mxcUrl;
    auto slash = mxcUrl.find('/', prefix.size());
    if (slash == std::string::npos) return mxcUrl;
    std::string server = mxcUrl.substr(prefix.size(), slash - prefix.size());
    std::string mediaId = mxcUrl.substr(slash + 1);
    std::string base = homeserver;
    while (!base.empty() && base.back() == '/') base.pop_back();
    return base + "/_matrix/media/v3/download/" + server + "/" + mediaId;
}

std::string buildThumbnailUrl(const std::string& mxcUrl, const std::string& homeserver,
                                int w, int h, const std::string& method) {
    std::string dl = buildDownloadUrl(mxcUrl, homeserver);
    auto dlPos = dl.find("/download/");
    if (dlPos != std::string::npos) dl.replace(dlPos, 10, "/thumbnail/");
    std::ostringstream os;
    os << dl << "?width=" << w << "&height=" << h << "&method=" << method;
    return os.str();
}

bool needsThumbnail(const std::string& mimeType, int maxSize) {
    return mimeType.find("image/") == 0 || mimeType.find("video/") == 0;
}

std::pair<int,int> getThumbnailDimensions(int sw, int sh, bool portrait) {
    if (portrait) return {sw / 2, sw / 2};
    return {sh / 2, sh / 2};
}

bool isValidMxcUrl(const std::string& url) {
    return url.compare(0, 6, "mxc://") == 0;
}

std::string extractMxcServer(const std::string& mxcUrl) {
    auto slash = mxcUrl.find('/', 6); // after "mxc://"
    if (slash == std::string::npos) return "";
    return mxcUrl.substr(6, slash - 6);
}

std::string extractMxcMediaId(const std::string& mxcUrl) {
    auto slash = mxcUrl.find('/', 6);
    if (slash == std::string::npos) return "";
    return mxcUrl.substr(slash + 1);
}

std::string formatMediaAttribution(const std::string& author, const std::string& license) {
    if (author.empty()) return "";
    std::ostringstream os;
    os << "By " << author;
    if (!license.empty()) os << " (" << license << ")";
    return os.str();
}

} // namespace progressive
