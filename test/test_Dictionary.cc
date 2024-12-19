#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <cassert>
#include <string.h>
#include <algorithm>
#include "Dictionary.h"
#include <unordered_set>
#include <boost/functional/hash.hpp>

using boost::hash;
using boost::hash_combine;
using std::cout;
using std::min;
using std::pair;
using std::set;
using std::string;
using std::unordered_set;
using std::vector;

void cdoQuery(string _sought);

// 1. 求取一个字符占据的字节数
size_t nBytesCode(const char ch);
// 2. 求取一个字符串的字符长度
std::size_t length(const std::string &str);
// 3. 中英文通用的最小编辑距离算法
int editDistance(const std::string &lhs, const std::string &rhs);

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

void cdoQuery(string _sought)
{

    Dictionary &dictionary = Dictionary::getInstance();
    unordered_set<pair<string, int>, hash<pair<string, int>>> resultSet;

    vector<char> goal(_sought.begin(), _sought.end());
    for (int i = 0; i < goal.size(); i++)
    {
        // 将 char 转换为 string
        string query = string(1, goal[i]);
        cout << query << "\n";
        vector<pair<string, int>> result = dictionary.doQuery("世");
        for (auto &item : result)
        {
            // cout << item.first << " " << item.second << "\n";
            resultSet.insert(item);
        }
    }

    for (const auto &item : resultSet)
    {
        cout << item.first << " " << item.second << " " << "\n";
        // if (editDistance(item.first, _sought) < 3)
        // {
        //     cout << item.first << " " << item.second << " " << "\n";
        // }
    }
}

void testDoQuery()
{
    Dictionary &dict = Dictionary::getInstance();
    dict.loadAllData("data/en.dat", "data/cn.dat", "data/en_index.dat", "data/cn_index.dat");
    // dict.queryIndex("世");
    // dict.showdIndexTable();
    cdoQuery("hello");
}
int main()
{
    testDoQuery();

    std::cout << "所有测试通过！" << std::endl;
    return 0;
}

size_t nBytesCode(const char ch)
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
std::size_t length(const std::string &str)
{
    std::size_t ilen = 0;
    for (std::size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
int triple_min(const int &a, const int &b, const int &c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int editDistance(const std::string &lhs, const std::string &rhs)
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
