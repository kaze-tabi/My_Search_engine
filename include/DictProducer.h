#ifndef __DICT_PRODUCER_H__
#define __DICT_PRODUCER_H__

#include "SplitToolCppJieba.h"
#include <string>
#include <vector>
#include <set>
#include <map>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

class DictProducer
{
public:
    DictProducer(const string &dir, const string &stopWordsPath); // 构造函数（英文）

    DictProducer(const string &dir, const string &stopWordsPath, SplitToolCppJieba *splitTool); // 构造函数（中文）

    void buildEnDict(); // 构造英文词典

    void buildCnDict(); // 构造中文词典

    void createIndex(); // 构造词典位置索引

    void storeDict();

    void storeIndex();
    
    set<string> loadStopWords(const string &stopWordsPath);

    /*测试用*/
    void showDict();  // 显示词典
    void showFiles(); // 显示语料库文件

private:
    vector<string> _files;        // 语料库文件的绝对路径
    map<string, int> _dict;       // 词典
    map<string, set<int>> _index; // 词典索引
    SplitToolCppJieba *_cuttor;   // 分词工具
    string _stop_words_path;      // 停用词文件绝对路径
    int _en_cn = 0;
};
#endif //__DICT_PRODUCER_H__