#include "WebPageQuery.h"

WebPageQuery * WebPageQuery::_WebPageQuery = nullptr;

WebPageQuery::WebPageQuery()
{
    _p_split_tool = new SplitToolCppJieba();
    loadWebPageFile();
}

WebPageQuery * WebPageQuery::getInstance()
{
    if(_WebPageQuery == nullptr)
    {
        _WebPageQuery = new WebPageQuery();
    }

    return _WebPageQuery;
}

void WebPageQuery::delInstance()
{
    if(_WebPageQuery)
    {
        delete _WebPageQuery;
        _WebPageQuery = nullptr;
    }
}

void WebPageQuery::loadWebPageFile()
{
    ifstream unrepeated_offset_lib_ifs(Configuration::getInstance()->getConfig("unrepeated_offsetlib.dat"));
    ifstream invert_index_lib_ifs(Configuration::getInstance()->getConfig("invert_index_lib.dat"));

    string line;
    while(getline(unrepeated_offset_lib_ifs, line))
    {
        istringstream iss(line);
        
        int doc_id = 0, offset = 0, page_len = 0;

        iss >> doc_id >> offset >> page_len;

        _offset_lib_ves.emplace_back(offset, page_len);
    }

    while(getline(invert_index_lib_ifs, line))
    {
        istringstream iss(line);

        string word;

        int doc_id = 0;

        double weight = 0;

        iss >> word;

        while(!iss.eof())
        {
            iss >> doc_id >> weight;

            _invert_index_lib[word][doc_id] = weight;
        }
    }
}

vector<pair<int, int>> & WebPageQuery::getOffsetLib()
{
    return _offset_lib_ves;
}

unordered_map<string, unordered_map<int, double>> & WebPageQuery::getInvertIndexLib()
{
    return _invert_index_lib;
}

SplitTool * WebPageQuery::getSpliTool()
{
    return _p_split_tool;
}
