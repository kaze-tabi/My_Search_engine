#ifndef __WEB_PAGE_QUERY_H__
#define __WWB_PAGE_QUERY_H__

#include "Configuration.h"
#include "SplitToolCppJieba.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <utility>

// 引入标准库类型别名，减少代码冗余
using std::vector;
using std::string;
using std::map;
using std::unordered_map;
using std::pair;
using std::set;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;


class WebPageQuery
{
public:
   
    static WebPageQuery * getInstance();

    static void delInstance();

    vector<pair<int, int>> & getOffsetLib();

    unordered_map<string, unordered_map<int, double>> & getInvertIndexLib();

    SplitTool * getSpliTool();

private:
    // 私有构造函数，防止外部实例化
    WebPageQuery();

    // 删除复制构造函数和赋值操作符，防止对象被复制
    WebPageQuery(const WebPageQuery & rhs) = delete;
    WebPageQuery(Configuration && rhs) = delete;
    WebPageQuery & operator=(const WebPageQuery & rhs) = delete;
    WebPageQuery & operator=(WebPageQuery && rhs)      = delete;

    // 加载网页文件到内存中的函数
    void loadWebPageFile();

private:
    static WebPageQuery * _WebPageQuery; // 单例模式的静态实例指针

    SplitTool *_p_split_tool = nullptr; // 分词工具指针

    map<string, set<int>> _word_index_map;  // 词频字典索引表，存储单词及其出现文档的索引

    vector<pair<int, int>> _offset_lib_ves; // 去重网页偏移库，存储文档的偏移量信息

    unordered_map<string, unordered_map<int, double>> _invert_index_lib;    // 去重网页倒排索引库，存储单词及其出现文档的相关性评分
};

#endif  // __WEB_PAGE_QUERY_H__