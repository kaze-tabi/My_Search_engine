#ifndef __SPLIT_TOOL_CPP_JIEBA_H__
#define __SPLIT_TOOL_CPP_JIEBA_H__

#include "SplitTool.h"
#include "../vendor/cppjieba/Jieba.hpp"

class SplitToolCppThulac : public SplitTool
{
public:
    vector<string> cut(const string &sentence);
};

#endif //__SPLIT_TOOL_CPP_THULAC_H__