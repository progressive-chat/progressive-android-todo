#include "progressive/matrix_error_utils.hpp"
#include <sstream>
namespace progressive {
std::string formatMatrixError(const std::string& code, const std::string& err) { return code+": "+err; }
bool isRetryableError(const std::string& c){return c=="M_LIMIT_EXCEEDED"||c=="M_SERVER_NOT_TRUSTED";}
bool isAuthError(const std::string& c){return c=="M_UNKNOWN_TOKEN"||c=="M_MISSING_TOKEN";}
bool isRateLimitError(const std::string& c){return c=="M_LIMIT_EXCEEDED";}
std::string getFriendlyErrorMessage(const std::string& c){
    if(c=="M_FORBIDDEN")return"You don't have permission"; if(c=="M_NOT_FOUND")return"Not found";
    if(c=="M_UNKNOWN_TOKEN")return"Session expired — please login again"; return c;
}
}
