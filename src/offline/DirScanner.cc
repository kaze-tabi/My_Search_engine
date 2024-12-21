#include "DirScanner.h"
#include <dirent.h>
#include <string.h>
#include <iostream>

using std::cout;

vector<string> &DirScanner::getFiles()
{
    for (auto &file : _files)
    {
        cout << file << "\n";
    }
}

void DirScanner::traverse(const string &dir)
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