#include "DictProducer.h"
int main(){
    string str = "test";
    DictProducer dict(str);
    dict.buildCnDict();
    return 0;
}