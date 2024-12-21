#ifndef __SPLIT_TOOL_CPP_JIEBA_H__
#define __SPLIT_TOOL_CPP_JIEBA_H__

#include "SplitTool.h"
#include "../vendor/simhash/cppjieba/Jieba.hpp"
#include "Configuration.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

class SplitToolCppJieba : public SplitTool
{
public:
    SplitToolCppJieba();

    ~SplitToolCppJieba();

    virtual vector<string> cut(const string & file_content) override;

private:
    cppjieba::Jieba * _jieba;
};

#endif //__SPLIT_TOOL_CPP_THULAC_H__