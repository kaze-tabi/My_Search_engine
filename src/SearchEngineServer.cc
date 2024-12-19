/**
 * Project SearchEngine
 */

#include "SearchEngineServer.h"
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <wfrest/json.hpp>


#include <iostream>

using namespace wfrest;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void SearchEngineServer::start(unsigned short port)
{ 
    if (_httpserver.track().start(port) == 0)
    {
        cout << "Server started on port " << port << endl;
        _httpserver.list_routes();
        _waitGroup.wait();
        _httpserver.stop();
    }
    else
    {
        cout << "Failed to start server on port " << port << endl;
    }
}

// 加载模块
void SearchEngineServer::loadModules()
{
    // 连接事件
    onConnection(); 

    // 消息事件
    onMessage();

    // 关闭事件
    onClose();

    // 线程池
    doTaskThread();

    // 加载搜索模块
    loadSearchModule();

    // 加载索引模块
    loadIndexModule();

    // 加载爬虫模块
    loadCrawlerModule();
}

// 停止服务器
void SearchEngineServer::stop() {}

// 连接事件
void SearchEngineServer::onConnection() {}

// 消息事件
void SearchEngineServer::onMessage() {}

// 关闭事件
void SearchEngineServer::onClose() {}

// 线程池
void SearchEngineServer::doTaskThread() {}

// 加载搜索模块
void SearchEngineServer::loadSearchModule() {}

// 加载索引模块
void SearchEngineServer::loadIndexModule() {}

// 加载爬虫模块
void SearchEngineServer::loadCrawlerModule() {}