#include "DictProducer.h"
int main()
{
    string str = "test";
    DictProducer dict("data/yuliao/en", "data/stop_words_eng.txt");
    dict.buildEnDict();
    // dict.showDict();
    dict.showFiles();
    return 0;
}