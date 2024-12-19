#include "SearchEngineServer.h"

int main()
{
    SearchEngineServer server(4); // 初始化线程池大小为4
    server.loadModules(); // 加载所有模块
    server.start(8080); // 启动HTTP服务器在端口8080

    // 保持服务器运行
    while (true) {
        // 服务器主循环
    }

    return 0;
}