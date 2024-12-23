#include "KeyRecommander.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <queue>
#include "../vendor/nlohmann/json.hpp"

using boost::hash;
using boost::hash_combine;
using std::min;
using std::string;
using std::unordered_set;
using std::vector;

namespace std
{
    template <>
    struct hash<pair<string, int>>
    {
        size_t operator()(const std::pair<std::string, int> &p) const
        {
            size_t seed = 0;
            hash_combine(seed, p.first);
            hash_combine(seed, p.second);
            return seed;
        }
    };
}

KeyRecommander::KeyRecommander(string sought) : _sought(sought)
{
}

int KeyRecommander::distance(string candidate)
{
    return editDistance(candidate, _sought);
}

void KeyRecommander::doQuery()
{

    Dictionary &dictionary = Dictionary::getInstance();
    unordered_set<pair<string, int>, hash<pair<string, int>>> resultSet;

    vector<string> result;
    auto it = _sought.begin();

    while (it != _sought.end())
    {
        // 解析下一个 UTF-8 字符
        unsigned char lead = *it;
        int num_bytes = 1;
        if ((lead & 0x80) == 0x00)
        { // 1-byte sequence
          // Already set to 1
        }
        else if ((lead & 0xE0) == 0xC0)
        { // 2-byte sequence
            num_bytes = 2;
        }
        else if ((lead & 0xF0) == 0xE0)
        { // 3-byte sequence
            num_bytes = 3;
        }
        else if ((lead & 0xF8) == 0xF0)
        { // 4-byte sequence
            num_bytes = 4;
        }

        // 提取当前 UTF-8 字符
        string current_char(it, it + num_bytes);

        // 添加到结果列表
        result.push_back(current_char);

        // 移动到下一个字符
        it += num_bytes;
    }

    for (auto &query : result)
    {
        vector<pair<string, int>> result = dictionary.doQuery(query);
        for (auto &item : result)
        {
            resultSet.insert(item);
        }
    }

    for (const auto &item : resultSet)
    {
        _resultQue.push(CandidateResult(item.first, item.second, distance(item.first)));
    }
}

size_t KeyRecommander::nBytesCode(const char ch)
{
    if (ch & (1 << 7))
    {
        int nBytes = 1;
        for (int idx = 0; idx != 6; ++idx)
        {
            if (ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
}
size_t KeyRecommander::length(const std::string &str)
{
    size_t ilen = 0;
    for (size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
int KeyRecommander::triple_min(const int &a, const int &b, const int &c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int KeyRecommander::editDistance(const std::string &lhs, const std::string &rhs)
{
    // 计算最小编辑距离-包括处理中英文
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1];
    for (size_t idx = 0; idx <= lhs_len; ++idx)
    {
        editDist[idx][0] = idx;
    }
    for (size_t idx = 0; idx <= rhs_len; ++idx)
    {
        editDist[0][idx] = idx;
    }
    std::string sublhs, subrhs;
    for (std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i,
                     ++lhs_idx)
    {
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);
        for (std::size_t dist_j = 1, rhs_idx = 0;
             dist_j <= rhs_len; ++dist_j, ++rhs_idx)
        {
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if (sublhs == subrhs)
            {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j -
                                                                1];
            }
            else
            {
                editDist[dist_i][dist_j] =
                    triple_min(editDist[dist_i][dist_j - 1] + 1,
                               editDist[dist_i - 1][dist_j] + 1,
                               editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}

string KeyRecommander::getResult()
{
    std::vector<CandidateResult> recommend_results;

    // 将队列中的元素保存到临时向量中
    while (!_resultQue.empty())
    {
        recommend_results.push_back(_resultQue.top());
        _resultQue.pop();
    }

    nlohmann::json res_json;

    // 将结果添加到 JSON 中
    for (const auto &result : recommend_results)
    {
        res_json.push_back(result._word.first);
    }

    // 将临时向量中的元素重新推入优先队列
    for (auto it = recommend_results.rbegin(); it != recommend_results.rend(); ++it)
    {
        _resultQue.push(*it);
    }

    return res_json.dump();
}