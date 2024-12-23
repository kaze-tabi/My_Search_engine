#ifndef __CACHE_MANAGER_H__
#define __CACHE_MANAGER_H__

#include "SynCacge.h"
#include "Configuration.h"
#include "DoubleLRU.h"

/**
 * CacheManager类负责管理多个线程的缓存操作。
 * 它提供了获取线程特定缓存、更新所有线程缓存以及生成操作序列的方法。
 */
class CacheManager
{
public:
    /**
     * 获取指定线程ID的缓存对象。
     * 
     * @param thread_id 线程ID，用于标识特定的线程。
     * @return 返回与线程ID关联的缓存对象指针。
     */
    LRUcache * getThreadCache(pid_t thread_id);

public:
    /**
     * 更新所有线程的缓存。
     * 此函数遍历所有线程缓存，并执行更新操作以保持数据新鲜。
     */
    void updateAllThreadCache();

    /**
     * 生成一系列操作序列，用于描述如何处理缓存项。
     * 
     * @param operator_sequence_list 一个列表，包含一系列操作对，每个操作对包括操作名称和操作对象。
     */
    void generateOperateSequence(list<pair<string, string>> & operator_sequence_list);

    /**
     * 更新所有线程的双缓存结构。
     * 此函数专注于更新采用双缓存机制的缓存，以确保高效和一致的数据管理。
     */
    void updateAllThreadDoubleCache();

private:
    /**
     * 一个无序映射，用于存储线程ID和对应的缓存对象指针。
     * 这使得可以根据线程ID快速查找特定线程的缓存。
     */
    unordered_map<pid_t, LRUcache *> _tid_cache_map;
};

#endif  //__CACHE_MANAGER_H__