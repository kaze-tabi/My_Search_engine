#include "DictProducer.h"
#include "../vendor/cppjieba/Jieba.hpp"
#include <iostream>

using namespace std;
int main()
{

    {
        DictProducer en_dict("data/yuliao/en", "data/stop_words_eng.txt");
        en_dict.buildEnDict();
        //en_dict.showDict();
        en_dict.storeDict();
        en_dict.createIndex();
        en_dict.storeIndex();

    }

    {
        SplitToolCppJieba *splitter = new SplitToolCppJieba;
        DictProducer cn_dict("data/yuliao/cn", "data/stop_words_zh.txt", splitter);
        cn_dict.buildCnDict();
        cn_dict.storeDict();
        cn_dict.createIndex();
        //cn_dict.showFiles();
        cn_dict.storeIndex();
        delete splitter;
    }

    return 0;
}