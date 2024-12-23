#ifndef __CANDIDATE_RESULT_H__
#define __CANDIDATE_RESULT_H__

#include <string>
#include <utility>

using std::string;
using std::pair;

class CandidateResult
{
public:
    CandidateResult(string word, int freq, int dist) noexcept;

    bool operator<(const CandidateResult& other) const {
        if (_word.second.second != other._word.second.second) {
            return _word.second.second > other._word.second.second;
        }
        return _word.second.first < other._word.second.first;
    }

public:
    pair<string, pair<int, int>> _word;
};

#endif //__CANDIDATE_RESULT_H__