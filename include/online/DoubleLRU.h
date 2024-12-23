#ifndef __DOUBLE_LRU_H__
#define __DOUBLE_LRU_H__

#include "LRUCache.h"
#include "Configuration.h"
#include <mutex>

using std::mutex;
using std::lock_guard;

class DoubleLRU;

class SubLRUCache
{
friend class DoubleLRU;

public:
    SubLRUCache();

    pair<string, string> getKV(string key);

    bool setKV(string key, string value);

    unordered_map<string, list<pair<string, string>>::iterator> & getSearchMap();

    list<pair<string, string>> & getLRUCacheContent();

private:
    bool noSwapOut(pair<string, string> key_value);

    void updataLRUCacheOrder(pair<string, string> key_value);

private:
    int _LRUCache_size;

    bool _is_lock;

    mutex _LRUCache_lock;

    unordered_map<string, list<pair<string, string>>::iterator> _search_map;

    list<pair<string, string>> _LRUCache_content;
};

class DoubleLRU : public LRUcache
{
public:
    DoubleLRU();

    virtual pair<string, string> getKV(string key) override;

    virtual bool setKV(string key, string value) override;

    virtual bool updataLRU() override;

    virtual list<pair<string, string>> & getPendingList();

    virtual mutex & getLRULock();

public:
    void swapLRUCache();

private:
    SubLRUCache  _read_LRUCache;
    
    SubLRUCache  _syn_LRUCache;
};

#endif
