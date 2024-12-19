/**
 * Project SearchEngine
 */

#ifndef __SEARCH_ENGINE_SERVER_H__
#define __SEARCH_ENGINE_SERVER_H__

#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>

class SearchEngineServer
{
public:
    SearchEngineServer(int cnt)
        : _waitGroup(cnt)
    {
    }
    ~SearchEngineServer() {}

    // 启动服务器
    void start(unsigned short port);

    // 加载模块
    void loadModules();

    // 停止服务器
    void stop();

private:
    // 连接事件
    void onConnection();

    // 消息事件
    void onMessage();

    // 关闭事件
    void onClose();

    // 线程池
    void doTaskThread();

    // 加载搜索模块
    void loadSearchModule();

    // 加载索引模块
    void loadIndexModule();

    // 加载爬虫模块
    void loadCrawlerModule();

private:
    WFFacilities::WaitGroup _waitGroup;// 线程池
    wfrest::HttpServer _httpserver; // http服务器
};

#endif //__SEARCH_ENGINE_SERVER_H__