/**
 * Project SearchEngine
 */
#ifndef _KEY_RECOMMANDER_H
#define _KEY_RECOMMANDER_H

//#include "priority_queue.h"
#include "CandidateResult.h"
#include <string>
#include <queue>
#include <vector>
#include <set>

using std::string;

class KeyRecommander {
public: 
    
void doQuery();
 // 计算编辑距离
int distance(string candidate);

vector<string> split_utf8_string(const string utf8_str);

size_t nBytesCode(const char ch);
size_t length(const std::string &str);
int triple_min(const int &a, const int &b, const int &c);
int editDistance(const std::string &lhs, const std::string &rhs);

private:
    string _sought;
    std::priority_queue<CandidateResult> _resultQue; 
    //TcpConnection _conn;
};

#endif //_KEYRECOMMANDER_H