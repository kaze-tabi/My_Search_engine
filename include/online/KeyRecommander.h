
#ifndef __KEY_RECOMMANDER_H__
#define __KEY_RECOMMANDER_H__

// #include "priority_queue.h"
#include "CandidateResult.h"
#include "Dictionary.h"
#include <string>
#include <queue>
#include <vector>
#include <set>

using std::string;

/**
 * KeyRecommander 类用于基于输入字符串进行关键词推荐。
 * 它通过编辑距离算法计算字符串之间的相似度，并根据计算结果推荐最相似的结果。
 */
class KeyRecommander
{
public:

    KeyRecommander(string sought);

    void doQuery();

    int distance(string candidate);

    string getResult();

    size_t nBytesCode(const char ch);

    size_t length(const std::string &str);

    int triple_min(const int &a, const int &b, const int &c);

    int editDistance(const string &lhs, const string &rhs);

private:
    /**
     * 存储要搜索的字符串。
     */
    string _sought;

    /**
     * 存储候选结果的优先队列。
     */
    std::priority_queue<CandidateResult> _resultQue;
    // TcpConnection _conn;
};

#endif //__KEY_RECOMMANDER_H__