#include "../vendor/THULAC/thulac.h"
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

void print(const THULAC_result& result, bool seg_only, char separator) {
    for(int i = 0; i < result.size() - 1; i++) {
        if(i != 0) cout << " ";
        if(seg_only) {
            cout << result[i].first;
        }
        else {
            cout << result[i].first ;
        }
    }
    cout << endl;
}

int main(){

 THULAC lac;
    lac.init("../models", nullptr, 0, 0, 0);
    THULAC_result result;
    clock_t start = clock();
    lac.cut("赞美耀神！", result);
    print(result, 0, '_');
    return 0;
}