#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../vendor/nlohmann/json.hpp"
#include <set>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::min;
using std::pair;
using std::set;
using std::string;
using std::to_string;
using std::vector;

// 构造函数变为私有
Dictionary::Dictionary() {}

vector<pair<string, int>> Dictionary::doQuery(const string &key)
{
    vector<pair<string, int>> results;
    queryIndex(key);
    //showdIndexTable();
    if (isChineseString(key))
    {
        for (int index : _indexTable[key])
        {
            results.push_back(_chineseDict[index - 1]);
            
        }
    }
    else if (!isChineseString(key))
    {
        for (int index : _indexTable[key])
        {
            results.push_back(_englishDict[index - 1]);
            
        }
    }

    return results;
}

void Dictionary::loadAllData(const string &enDictFile, const string &cnDictFile, const string &enIndexFile, const string &cnIndexFile)
{

    loadEnDictFromFile(enDictFile);
    loadCnDictFromFile(cnDictFile);
    loadEnIndexFromFile(enIndexFile);
    loadCnIndexFromFile(cnIndexFile);
}

void Dictionary::loadEnDictFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "无法打开词典文件: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string word;
        int freq;
        iss >> word >> freq;
        _englishDict.emplace_back(make_pair(word, freq));
    }
}

void Dictionary::loadCnDictFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "无法打开词典文件: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string word;
        int freq;
        iss >> word >> freq;
        _chineseDict.emplace_back(make_pair(word, freq));
    }
}

SplitTool * Dictionary::getSplitTool()
{
    return _splitTool;
}

void Dictionary::loadEnIndexFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "无法打开索引 JSON 文件: " << filename << endl;
        return;
    }

    nlohmann::json indexJson;
    try
    {
        file >> indexJson; // 将 JSON 内容读取到 indexJson 变量中
    }
    catch (nlohmann::json::parse_error &e)
    {
        cerr << "JSON 解析错误: " << e.what() << endl;
        return;
    }

    file.close();

    // 解析 JSON 并填充到相应的索引表中
    for (auto &[word, indices] : indexJson.items())
    {
        set<int> indexSet;
        for (auto &index : indices)
        {
            indexSet.insert(index.get<int>());
        }
        _englishIndex[word] = indexSet;
    }
}

void Dictionary::loadCnIndexFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "无法打开索引 JSON 文件: " << filename << endl;
        return;
    }

    nlohmann::json indexJson;
    try
    {
        file >> indexJson; // 将 JSON 内容读取到 indexJson 变量中
    }
    catch (nlohmann::json::parse_error &e)
    {
        cerr << "JSON 解析错误: " << e.what() << endl;
        return;
    }

    file.close();

    // 解析 JSON 并填充到相应的索引表中
    for (auto &[word, indices] : indexJson.items())
    {
        set<int> indexSet;
        for (auto &index : indices)
        {
            indexSet.insert(index.get<int>());
        }
        _chineseIndex[word] = indexSet;
    }
}

void Dictionary::queryIndex(const string key)
{
    if (isChineseString(key))
    {
        // 查询中文索引
        auto it = _chineseIndex.find(key);
        if (it != _chineseIndex.end())
        {
            _indexTable[key] = it->second;
        }
    }
    else
    {
        // 查询英文词典
        auto it = _englishIndex.find(key);
        if (it != _englishIndex.end())
        {
            _indexTable[key] = it->second;
        }
    }
}

bool Dictionary::isChineseString(const std::string &str)
{
    int chineseCharCount = 0;
    int totalCharCount = 0;

    for (size_t i = 0; i < str.size(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if (c >= 0xE0 && c <= 0xEF)
        {
            // Check for UTF-8 encoded Chinese characters
            if (i + 2 < str.size())
            {
                unsigned char c1 = static_cast<unsigned char>(str[i + 1]);
                unsigned char c2 = static_cast<unsigned char>(str[i + 2]);
                uint32_t codePoint = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);

                if ((codePoint >= 0x4E00 && codePoint <= 0x9FA5) ||
                    (codePoint >= 0x3400 && codePoint <= 0x4DBF) ||
                    (codePoint >= 0x20000 && codePoint <= 0x2A6DF) ||
                    (codePoint >= 0x2A700 && codePoint <= 0x2B73F) ||
                    (codePoint >= 0x2B740 && codePoint <= 0x2B81F) ||
                    (codePoint >= 0x2B820 && codePoint <= 0x2CEAF) ||
                    (codePoint >= 0xF900 && codePoint <= 0xFAFF) ||
                    (codePoint >= 0x2F800 && codePoint <= 0x2FA1F))
                {
                    chineseCharCount++;
                    i += 2;
                }
            }
        }
        totalCharCount++;
    }

    return (chineseCharCount * 1.0 / totalCharCount) > 0.5;
}

void Dictionary::showdEnDict()
{
    for (auto &[word, freq] : _englishDict)
    {
        cout << word << " " << freq << endl;
    }
}
void Dictionary::showdCnDict()
{
    for (auto &[word, freq] : _chineseDict)
    {
        cout << word << " " << freq << endl;
    }
}
void Dictionary::showdEnIndex()
{
    for (auto &[word, indices] : _englishIndex)
    {
        cout << word << ": ";
        for (auto &index : indices)
        {
            cout << index << " ";
        }
        cout << endl;
    }
}

void Dictionary::showdCnIndex()
{
    for (auto &[word, indices] : _chineseIndex)
    {
        cout << word << ": ";
        for (auto &index : indices)
        {
            cout << index << " ";
        }
        cout << endl;
    }
}
void Dictionary::showdIndexTable()
{
    for (auto &[word, freq] : _indexTable)
    {
        cout << word << ": ";
        for (auto &index : freq)
        {
            cout << index << " ";
        }
        cout << endl;
    }
}