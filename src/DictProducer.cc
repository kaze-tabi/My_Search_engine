#include "DictProducer.h"
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "../vendor/nlohmann/json.hpp"

using std::cout;
using std::ifstream;
using std::istreambuf_iterator;
using std::istringstream;
using std::map;
using std::remove;
using std::string;
using std::vector;
using nlohmann::json;

DictProducer::DictProducer(const string &dir, const string &stopWordsPath)
    : _stop_words_path(stopWordsPath), _en_cn(0)
{
    // 获取所有文件名
    DIR *dirp;
    struct dirent *dirent;
    // 打开目录
    dirp = opendir(dir.c_str());
    if (NULL == dirp)
    {
        perror("opendir error:");
        exit(-1);
    }
    // 遍历目录
    while (NULL != (dirent = readdir(dirp)))
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
            continue;
        string path = dir + "/" + dirent->d_name;
        _files.push_back(path);
    }
    closedir(dirp);
}

DictProducer::DictProducer(const string &dir, const string &stopWordsPath, SplitToolCppJieba *splitTool)
    : _stop_words_path(stopWordsPath), _cuttor(splitTool), _en_cn(1)
{
    // 获取所有文件名
    DIR *dirp;
    struct dirent *dirent;
    // 打开目录
    dirp = opendir(dir.c_str());
    if (NULL == dirp)
    {
        perror("opendir error:");
        exit(-1);
    }
    // 遍历目录
    while (NULL != (dirent = readdir(dirp)))
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
            continue;
        string path = dir + "/" + dirent->d_name;
        _files.push_back(path);
    }
    closedir(dirp);
}

// 构造英文词典
void DictProducer::buildEnDict()
{
    set<string> stopwords = loadStopWords(_stop_words_path);

    // 遍历所有文件
    for (const auto &file : _files)
    {
        cout << "Processing file: " << file << "\n";
        ifstream infile(file);
        if (!infile.is_open())
        {
            perror("Failed to open file");
            exit(-1);
        }
        // 读取文件内容
        string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
        cout << "File size: " << content.size() << "\n";
        // 将标点符号替换为空格
        for (auto &ch : content)
        {
            if (!std::isalnum(ch) && !std::isspace(ch))
            {
                ch = ' ';
            }
            if (ch >= 'A' && ch <= 'Z')
            {
                ch += 32;
            }
        }

        istringstream iss(content);
        string word;
        while (iss >> word)
        {
            if (!word.empty() && (stopwords.find(word) == stopwords.end()))
            {
                if (_dict.find(word) == _dict.end())
                {
                    _dict[word] = 1;
                }
                else
                {
                    _dict[word] += 1;
                }
            }
        }
        infile.close();
    }
}

void DictProducer::buildCnDict()
{
    set<string> stopwords = loadStopWords(_stop_words_path);
    // 遍历所有文件
    for (const auto &file : _files)
    {
        cout << "Processing file: " << file << "\n";
        ifstream infile(file);
        if (!infile.is_open())
        {
            perror("Failed to open file");
            exit(-1);
        }
        // 读取文件内容
        string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
        // cout << "File size: " << content.size() << "\n";
        content.erase(remove(content.begin(), content.end(), '\n'), content.end());
        vector<string> iss = _cuttor->cut(content);

        for (auto &word : iss)
        {
            if (!word.empty() && (stopwords.find(word) == stopwords.end()))
            {
                if (_dict.find(word) == _dict.end())
                {
                    _dict[word] = 1;
                }
                else
                {
                    _dict[word] += 1;
                }
            }
        }
        infile.close();
    }
}

void DictProducer::createIndex()
{

    // 将 map<string, int> 转换为 vector<pair<string, int>>
    std::vector<std::pair<std::string, int>> dictVector(_dict.begin(), _dict.end());

    unsigned int subscript = 1;
    for (auto &it : dictVector)
    {
        string word = it.first;
        if (_en_cn == 1) // 英文
        {
            for (int i = 0; i < int(word.size()); ++i)
            {
                if (!isalpha(word[i]))
                {
                    continue;
                }
                string letter(1, word[i]);
                _index[letter].insert(subscript);
            }
        }
        else if (_en_cn == 0) // 中文
        {
            int wordSize = word.size();
            int i = 0;
            while (i < wordSize)
            {
                int len = 1;
                for (int j = 0; j < 6 && (word[i] & (0x80 >> j)); j++)
                {
                    len = j + 1;
                }
                string letter = word.substr(i, len);
                _index[letter].insert(subscript);
                i += len;
            }
        }
        ++subscript;
    }
}

void DictProducer::storeDict()
{
    string dictFilePath;
    if (_en_cn == 0)
    {
        dictFilePath = "data/en.dat"; // 定义输出文件路径
    }
    else if (_en_cn == 1)
    {
        dictFilePath = "data/cn.dat"; // 定义输出文件路径
    }

    // 创建 JSON 对象
    json dictJson;
    for (const auto &entry : _dict)
    {
        dictJson[entry.first] = entry.second;
    }

    // 打开文件流
    std::ofstream outFile(dictFilePath);
    if (!outFile.is_open())
    {
        perror("Failed to open dictionary file for writing");
        exit(-1);
    }

    // 将 JSON 对象写入文件
    outFile << dictJson.dump(4); // 使用缩进为4的格式化输出

    // 关闭文件流
    outFile.close();
}

void DictProducer::showDict()
{
    // cout << "stopwords:\n";
    // for (auto& stopwd : _stopwords) {
    //     cout << stopwd << "\n";
    // }
    cout << "dict:\n";
    for (auto &dict : _dict)
    {
        cout << dict.first << ":" << dict.second << "\n";
    }
}

void DictProducer::showFiles()
{
    cout << "files:\n";
    for (const auto &file : _files)
    {
        cout << file << "\n";
    }
}

// 加载停用词并去除 \r
set<string> DictProducer::loadStopWords(const string &stopWordsPath)
{
    set<string> stopwords;
    ifstream infile(stopWordsPath);
    if (!infile.is_open())
    {
        perror("Failed to open stop words file");
        exit(-1);
    }
    // 一次性读取整个文件内容
    string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();

    // 使用 stringstream 分割字符串
    istringstream iss(content);
    string line;
    while (getline(iss, line))
    {
        // 去除 \r 字符
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if (!line.empty())
        {
            stopwords.insert(line);
        }
    }
    return stopwords;
}

void DictProducer::storeIndex()
{
    string indexFilePath;
    if (_en_cn == 0)
    {
        indexFilePath = "data/en_index.dat"; // 定义输出文件路径
    }
    else if (_en_cn == 1)
    {
        indexFilePath = "data/cn_index.dat"; // 定义输出文件路径
    } 

    // 创建 JSON 对象
    json indexJson;
    for (const auto &entry : _index)
    {
        indexJson[entry.first] = entry.second;
    }

    // 打开文件流
    std::ofstream outFile(indexFilePath);
    if (!outFile.is_open())
    {
        perror("Failed to open index file for writing");
        exit(-1);
    }

    // 将 JSON 对象写入文件
    outFile << indexJson.dump(4); // 使用缩进为4的格式化输出

    // 关闭文件流
    outFile.close();
}

