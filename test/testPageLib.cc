#include <iostream>
#include "PageLib.h"

int main()
{
    // 创建 PageLib 对象
    PageLib pageLib;
    std::cout << "Creating PageLib object...\n";
    // 创建网页库
    pageLib.create();
    std::cout << "Creating WebPage objects...\n";
    // 存储网页库和偏移库
    pageLib.store();

    std::cout << "PageLib processing completed successfully.\n";

    return 0;
}