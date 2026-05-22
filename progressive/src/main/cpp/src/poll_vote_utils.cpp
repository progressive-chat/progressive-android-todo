#include "progressive/poll_vote_utils.hpp"
#include <sstream>
#include <algorithm>
namespace progressive {
std::string buildPollVoteContent(const std::string& pid, const std::vector<std::string>& opts){ std::ostringstream os; os<<R"({"m.relates_to":{"event_id":")"<<pid<<R"(","rel_type":"m.annotation"})"; return os.str(); }
PollVote parsePollVote(const std::string& json){ PollVote v; return v; }
bool hasUserVoted(const std::vector<PollVote>& votes, const std::string& uid){ return std::any_of(votes.begin(),votes.end(),[&](auto&v){return v.userId==uid;}); }
int countVotesForOption(const std::vector<PollVote>& votes, const std::string& oid){ int c=0; for(auto&v:votes) if(std::find(v.selectedOptions.begin(),v.selectedOptions.end(),oid)!=v.selectedOptions.end())c++; return c; }
}
