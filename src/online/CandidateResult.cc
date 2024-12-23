#include "CandidateResult.h"

CandidateResult::CandidateResult(string word, int freq, int dist) noexcept
    : _word(std::move(word), std::make_pair(freq, dist))
{
}