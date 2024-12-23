#ifndef __WEB_SEARCH_H__
#define __WEB_SEARCH_H__

#include "WebPageQuery.h"
#include "WebPage.h"
#include "../vendor/nlohmann/json.hpp"

#include <math.h>
#include <queue>
using std::priority_queue;

// 为std::less结构体模板提供特化版本，用于自定义priority_queue的比较方式
template <>
struct std::less<pair<int, double>>
{
    bool operator()(const pair<int, double> &lhs, const pair<int, double> &rhs)
    {
        if (lhs.second < rhs.second)
        {
            return false;
        }

        return true;
    }
};

/**
 * WebSearch类负责执行网页搜索任务。
 * 它通过分析查询词、计算网页相关性并生成搜索结果来工作。
 */
class WebSearch
{
public:
    // 构造函数，初始化WebSearch对象
    WebSearch();

    void doSearch(string query_word);

    string getResult();

private:
    void generateQueryWordVector(vector<string> &split_res, string query_word);

    void generateQueryWordFrequenceMap(map<string, int> &word_frequence_map, vector<string> split_res);

    void generateCandidateWebPageSet(set<int> &web_page_set, vector<string> split_res);

    void generateBaseVector(vector<double> &base_vector, map<string, int> &word_frequence_map, vector<string> split_res);

    void minMaxScaler(vector<double> &base_vector);

    void findCandidateWebPageID(map<int, vector<double>> &pages_feature_ves_map, set<int> &web_page_set, vector<string> split_res);

    void generateIdCosSimilarityVector(vector<pair<int, double>> &cos_similar_ves, map<int, vector<double>> &pages_feature_ves_map, vector<double> &base_vector);

    void generateCandidateDocIDVector(vector<int> &most_similar_doc_id_vec, vector<pair<int, double>> &cos_similar_ves);

    void generateWebPage(vector<int> &most_similar_doc_id_vec);

private:
    // 优先队列，用于存储和管理搜索结果
    priority_queue<pair<int, double>> _pri_que;

    // 存储搜索结果的向量
    vector<vector<string>> _res_ves;

    // 分词工具指针
    SplitTool *_p_split_tool;

    // 标记是否有搜索结果
    bool _no_result = false;
};

#endif  //__WEB_SEARCH_H__