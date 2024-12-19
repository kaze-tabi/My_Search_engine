/**
 * Project SearchEngine
 */
#ifndef _CANDIDATERESULT_H
#define _CANDIDATERESULT_H

#include <string>

using std::string;

class CandidateResult
{
public:
    CandidateResult(string word, int freq, int dist);

public:
    string _word;
    int _freq;
    int _dist;
};

CandidateResult::CandidateResult(string word, int freq, int dist)
    : _word(word), _freq(freq), _dist(dist)
{
}

struct CompareCandidateResult
{
    bool operator()(const CandidateResult &lhs, const CandidateResult &rhs) const
    {
        if (lhs._dist == rhs._dist)
        {
            return lhs._freq < rhs._freq;
        }
        return lhs._dist > rhs._dist;
    }
};

#endif //_CANDIDATERESULT_H