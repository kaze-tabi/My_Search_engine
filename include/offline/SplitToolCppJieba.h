#ifndef __SPLIT_TOOL_CPP_JIEBA_H__
#define __SPLIT_TOOL_CPP_JIEBA_H__

#include "SplitTool.h"
#include "../vendor/cppjieba/Jieba.hpp"

class SplitToolCppJieba : public SplitTool
{
private:
    cppjieba::Jieba _jieba;

public:
    SplitToolCppJieba();
    vector<string> cut(const string &sentence);
};

#endif //__SPLIT_TOOL_CPP_THULAC_H__