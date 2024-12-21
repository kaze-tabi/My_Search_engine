#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

class Dictionary
{
public:
    // 获取单例实例
    static Dictionary& getInstance()
    {
        static Dictionary instance;
        return instance;
    }

    // 删除拷贝构造函数和赋值操作符
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;
    // 查询词典
    vector<pair<string,int>> doQuery(const string &key);
    // 预热方法
    void loadAllData(const string &enDictFile, const string &cnDictFile, const string &enIndexFile, const string &cnIndexFile);
    // 判断是否为中文字符串
    bool isChineseString(const string &str);

    void showdEnDict();
    void showdCnDict();
    void showdEnIndex();
    void showdCnIndex();
    void showdIndexTable();
  // 生成索引
    void queryIndex(const string key);

private:
    Dictionary(); 
    // 加载英文词典
    void loadEnDictFromFile(const string &filename);
    // 加载中文词典
    void loadCnDictFromFile(const string &filename);
    // 加载英文索引
    void loadEnIndexFromFile(const string &filename);
    // 加载中文索引
    void loadCnIndexFromFile(const string &filename);
  

private:
    vector<pair<string, int>> _englishDict; // 英文词典
    vector<pair<string, int>> _chineseDict; // 中文词典
    map<string, set<int>> _englishIndex;    // 英文索引
    map<string, set<int>> _chineseIndex;    // 中文索引
    map<string, set<int>> _indexTable;      // 索引表
};

#endif //__DICTIONARY_H__