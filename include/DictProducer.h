#ifndef __DICT_PRODUCER_H__
#define __DICT_PRODUCER_H__

#include "SplitTool.h"
#include <string>
#include <vector>
#include <set>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::set; 
using std::map;

class DictProducer {
public:

DictProducer(string);

void buildEnDict();

void buildCnDict();

void createIndex();

void store();

private:

vector<string> _files;
vector<pair<string, int>> _dict;
map<string, set<int>> _index;
SplitTool * _cuttor;

};
#endif //__DICT_PRODUCER_H__