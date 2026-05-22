#pragma once
#include <string>
#include <vector>
namespace progressive {
struct PollVote { std::string pollId; std::string userId; std::vector<std::string> selectedOptions; };
std::string buildPollVoteContent(const std::string& pollId, const std::vector<std::string>& optionIds);
PollVote parsePollVote(const std::string& json);
bool hasUserVoted(const std::vector<PollVote>& votes, const std::string& userId);
int countVotesForOption(const std::vector<PollVote>& votes, const std::string& optionId);
}
