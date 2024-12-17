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

using std::cout;
using std::ifstream;
using std::istreambuf_iterator;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

DictProducer::DictProducer(const string &dir, const string &stopWordsPath)
    : _stop_words_path(stopWordsPath)
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

DictProducer::DictProducer(const string &dir, const string &stopWordsPath, SplitTool *splitTool)
{
}

// 构造英文词典
void DictProducer::buildEnDict()
{
    set<string> _stopwords;
    // 读取停词表
    ifstream infile(_stop_words_path);
    if (!infile.is_open())
    {
        perror("Failed to open file");
        exit(-1);
    }
    string line;
    while (getline(infile, line))
    {
        _stopwords.insert(line);
    }
    infile.close();

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
            if (!word.empty() && (_stopwords.find(word) == _stopwords.end()))
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
    set<string> _stopwords;
    // 读取停词表
    ifstream infile(_stop_words_path);
    if (!infile.is_open())
    {
        perror("Failed to open file");
        exit(-1);
    }
    string line;
    while (getline(infile, line))
    {
        _stopwords.insert(line);
    }
    infile.close();

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
        vector<string> iss = _cuttor->cut(content);

        for (auto &word : iss)
        {
            if (!word.empty() && (_stopwords.find(word) == _stopwords.end()))
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
    }
}

void DictProducer::createIndex()
{
}

void DictProducer::store()
{
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