/**
 * Project SearchEngine 目录扫描类 -- 递归扫描
 */

#ifndef _DIRSCANNER_H
#define _DIRSCANNER_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class DirScanner
{
public:
    vector<string> &getFiles(); // 返回_vecFilesfiles 的引用

    void traverse(const string &dir); // 遍历获取某一目录下的所有文件
                                      // private:
    vector<string> _files;            // 存放每个语料文件的绝对路径
};

#endif //_DIRSCANNER_H