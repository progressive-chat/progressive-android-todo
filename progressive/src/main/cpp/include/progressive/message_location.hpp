#pragma once
#include <string>
#include <cstdint>

namespace progressive {

struct GeoCoordinates {
    double latitude = 0.0;
    double longitude = 0.0;
    double accuracy = 0.0;  // meters, optional
};

// Parse "geo:lat,lon;u=accuracy" URI
GeoCoordinates parseGeoUri(const std::string& uri);
std::string buildGeoUri(const GeoCoordinates& coords);

// Parse "m.location" event content
struct LocationMessageContent {
    std::string body;          // e.g. "User shared their location"
    GeoCoordinates coords;
    std::string geoUri;
    std::string description;   // optional user description
    std::string assetType;     // "m.self" or custom
    int64_t timestampMs = 0;
};

LocationMessageContent parseLocationContent(const std::string& json);
std::string buildLocationContent(const LocationMessageContent& content);
std::string buildLocationContent(const GeoCoordinates& coords, const std::string& description);

// Map tile URL builder
std::string buildStaticMapUrl(const GeoCoordinates& coords, int zoom, int width, int height,
                               const std::string& mapProvider = "osm");

// Distance calculation (Haversine formula)
double haversineDistance(const GeoCoordinates& a, const GeoCoordinates& b);

} // namespace progressive
