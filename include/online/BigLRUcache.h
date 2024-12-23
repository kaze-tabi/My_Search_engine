#ifndef __BIG_LRU_CACHE_H__
#define __BIG_LRU_CACHE_H__

#include "LRUCache.h"
#include "Configuration.h"
#include <mutex>

using std::mutex;
using std::lock_guard;

class BigLRUcache
{
public:
    static BigLRUcache * getInstance();

public:
    pair<string, string> getKV(string key);
    bool setKV(string key, string value);
    bool updataCache();

private:
    BigLRUcache();

    BigLRUcache(const BigLRUcache & rhs) = delete;
    BigLRUcache(BigLRUcache && rhs) = delete;

    BigLRUcache & operator=(const BigLRUcache & rhs) = delete;
    BigLRUcache & operator=(BigLRUcache && rhs) = delete;

private:
    bool noSwapOut(pair<string, string> key_value);
    void updataCacheOrder(pair<string, string> key_value);
private:
    static BigLRUcache * _p_cache;

    unordered_map<string, list<pair<string, string>>::iterator> _search_map;

    list<pair<string, string>> _cache_content;

    mutex _lock;

    int _cache_size;
};

#endif  //__BIG_LRU_CACHE_H__
