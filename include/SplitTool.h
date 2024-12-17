/*纯抽象类*/

#ifndef __SPLIT_TOOL_H__
#define __SPLIT_TOOL_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class SplitTool
{
public:
    virtual vector<string> cut(const string &sentence) = 0;
};

#endif //__SPLIT_TOOL_H__