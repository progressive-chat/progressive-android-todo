#include "progressive/message_location.hpp"
#include <sstream>
#include <cmath>

namespace progressive {

GeoCoordinates parseGeoUri(const std::string& uri) {
    GeoCoordinates c;
    if (uri.compare(0, 4, "geo:") != 0) return c;
    auto comma = uri.find(',', 4);
    if (comma == std::string::npos) return c;
    try {
        c.latitude = std::stod(uri.substr(4, comma - 4));
        auto semi = uri.find(';', comma);
        c.longitude = std::stod(uri.substr(comma + 1, semi - comma - 1));
        auto acc = uri.find("u=", semi);
        if (acc != std::string::npos) {
            c.accuracy = std::stod(uri.substr(acc + 2));
        }
    } catch (...) {}
    return c;
}

std::string buildGeoUri(const GeoCoordinates& c) {
    std::ostringstream os;
    os << "geo:" << c.latitude << "," << c.longitude;
    if (c.accuracy > 0) os << ";u=" << (int)c.accuracy;
    return os.str();
}

static std::string extractJsonStr(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":\"");
    if (p == std::string::npos) return "";
    p += key.size() + 4;
    auto e = json.find('"', p);
    if (e == std::string::npos) return "";
    return json.substr(p, e - p);
}

LocationMessageContent parseLocationContent(const std::string& json) {
    LocationMessageContent c;
    c.body = extractJsonStr(json, "body");
    c.geoUri = extractJsonStr(json, "geo_uri");
    if (!c.geoUri.empty()) c.coords = parseGeoUri(c.geoUri);
    c.description = extractJsonStr(json, "description");
    c.assetType = extractJsonStr(json, "asset").empty() ? "m.self" : extractJsonStr(json, "asset");
    return c;
}

std::string buildLocationContent(const LocationMessageContent& content) {
    std::ostringstream os;
    os << "{";
    os << R"("msgtype":"m.location",)";
    os << R"("body":")" << content.body << R"(",)"
       << R"("geo_uri":")" << content.geoUri << R"(")";
    if (!content.description.empty()) os << R"(,"description":")" << content.description << R"(")";
    os << R"(,"org.matrix.msc3488.asset":{"type":")" << content.assetType << R"("})";
    os << "}";
    return os.str();
}

std::string buildLocationContent(const GeoCoordinates& coords, const std::string& description) {
    std::ostringstream os;
    os << "{";
    os << R"("msgtype":"m.location",)";
    os << R"("body":")" << description << R"(",)";
    os << R"("geo_uri":")" << buildGeoUri(coords) << R"(")";
    os << R"(,"org.matrix.msc3488.asset":{"type":"m.self"})";
    os << "}";
    return os.str();
}

std::string buildStaticMapUrl(const GeoCoordinates& coords, int zoom, int width, int height,
                               const std::string& mapProvider) {
    if (mapProvider == "osm") {
        std::ostringstream os;
        os << "https://staticmap.openstreetmap.de/staticmap.php?"
           << "center=" << coords.latitude << "," << coords.longitude
           << "&zoom=" << zoom << "&size=" << width << "x" << height
           << "&maptype=mapnik";
        return os.str();
    }
    // Default: MapLibre/Matrix tile server format
    std::ostringstream os;
    os << "https://api.maptiler.com/maps/streets/static/"
       << coords.longitude << "," << coords.latitude << "," << zoom
       << "/" << width << "x" << height << ".png";
    return os.str();
}

double haversineDistance(const GeoCoordinates& a, const GeoCoordinates& b) {
    const double R = 6371000.0; // Earth radius in meters
    double lat1 = a.latitude * M_PI / 180.0;
    double lat2 = b.latitude * M_PI / 180.0;
    double dlat = (b.latitude - a.latitude) * M_PI / 180.0;
    double dlon = (b.longitude - a.longitude) * M_PI / 180.0;
    double aa = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    return 2 * R * atan2(sqrt(aa), sqrt(1 - aa));
}

double calculateBearing(const GeoCoordinates& from, const GeoCoordinates& to) {
    double lat1 = from.latitude * M_PI / 180.0;
    double lat2 = to.latitude * M_PI / 180.0;
    double dlon = (to.longitude - from.longitude) * M_PI / 180.0;
    double y = sin(dlon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dlon);
    return fmod(atan2(y, x) * 180.0 / M_PI + 360.0, 360.0);
}

GeoCoordinates calculateDestination(const GeoCoordinates& origin, double bearing, double distanceM) {
    const double R = 6371000.0;
    double lat1 = origin.latitude * M_PI / 180.0;
    double lon1 = origin.longitude * M_PI / 180.0;
    double brng = bearing * M_PI / 180.0;
    double dR = distanceM / R;
    double lat2 = asin(sin(lat1) * cos(dR) + cos(lat1) * sin(dR) * cos(brng));
    double lon2 = lon1 + atan2(sin(brng) * sin(dR) * cos(lat1), cos(dR) - sin(lat1) * sin(lat2));
    GeoCoordinates c;
    c.latitude = lat2 * 180.0 / M_PI;
    c.longitude = lon2 * 180.0 / M_PI;
    return c;
}

} // namespace progressive
