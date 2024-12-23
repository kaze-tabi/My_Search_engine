#include "DoubleLRU.h"

DoubleLRU::DoubleLRU():LRUcache()
{

}

pair<string, string> DoubleLRU::getKV(string key)
{
    return _read_LRUCache.getKV(key);
}

bool DoubleLRU::setKV(string key, string value)
{
    return _read_LRUCache.setKV(key, value);
}

bool DoubleLRU::updataLRU()
{
    swapLRUCache();

    return true;
}

void DoubleLRU::swapLRUCache()
{
    // 交换 syn_LRUCache 和 read_LRUCache 的内容
    
    lock_guard<mutex> read_lg(_read_LRUCache._LRUCache_lock);

    std::cout << "\t\tBefore Swap read : ";
    
    for(auto lit = _read_LRUCache._LRUCache_content.begin(); lit != _read_LRUCache._LRUCache_content.end(); ++lit)
    {
        std::cout << lit->first << " ";
    }

    std::cout << "\n\t\tBefore Swap syn  : ";

    for(auto lit = _syn_LRUCache._LRUCache_content.begin(); lit != _syn_LRUCache._LRUCache_content.end(); ++lit)
    {
        std::cout << lit->first << " ";
    }
    std::cout << "\n";


    std::swap(_read_LRUCache._LRUCache_content, _syn_LRUCache._LRUCache_content);
    std::swap(_read_LRUCache._search_map, _syn_LRUCache._search_map);
    

    std::cout << "\t\tAfter  Swap read : ";
    for(auto lit = _read_LRUCache._LRUCache_content.begin(); lit != _read_LRUCache._LRUCache_content.end(); ++lit)
    {
        std::cout << lit->first << " ";
    }
    std::cout << "\n\t\tAfter  Swap syn  : ";

    for(auto lit = _syn_LRUCache._LRUCache_content.begin(); lit != _syn_LRUCache._LRUCache_content.end(); ++lit)
    {
        std::cout << lit->first << " ";
    }
    std::cout << "\n";
}

list<pair<string, string>> & DoubleLRU::getPendingList()
{
    return _syn_LRUCache._LRUCache_content;
}

mutex & DoubleLRU::getLRULock()
{
    return _syn_LRUCache._LRUCache_lock;
}


/***********************************************************************************************************************************************/


SubLRUCache::SubLRUCache()
{
    _LRUCache_size = std::stoi(Configuration::getInstance()->getConfig("LRUCacheSize"));
}

pair<string, string> SubLRUCache::getKV(string key)
{
    lock_guard<mutex> lg(_LRUCache_lock);

    auto umit = _search_map.find(key);

    if(umit == _search_map.end())
    {
        return {"", ""};
    }
    else
    {
        auto lit = umit->second;

        noSwapOut(*lit);

        return *umit->second;
    }
}

bool SubLRUCache::setKV(string key, string value)
{
    lock_guard<mutex> lg(_LRUCache_lock);

    updataLRUCacheOrder({key, value});

    return true;
}

bool SubLRUCache::noSwapOut(pair<string, string> key_value)
{
    auto umit = _search_map.find(key_value.first);

    if(umit != _search_map.end())
    {
        auto lit = umit->second;

        if(lit->first == key_value.first)
        {
            _LRUCache_content.splice(_LRUCache_content.begin(), _LRUCache_content, lit);

            umit->second = _LRUCache_content.begin();

            return true;
        }
    }

    return false;
}

void SubLRUCache::updataLRUCacheOrder(pair<string, string> key_value)
{
    if(_LRUCache_content.size() < _LRUCache_size)
    {
        if(!noSwapOut(key_value))
        {
            _LRUCache_content.push_front(key_value);

            auto lit = _LRUCache_content.begin();
            _search_map[key_value.first] = lit;
        }
    }
    else
    {
        if(!noSwapOut(key_value))
        {
            auto erase_it = _LRUCache_content.rbegin();
            _search_map.erase(erase_it->first);

            _LRUCache_content.pop_back();
            _LRUCache_content.push_front(key_value);

            auto lit = _LRUCache_content.begin();
            _search_map[key_value.first] = lit;
        }
    }
}

unordered_map<string, list<pair<string, string>>::iterator> & SubLRUCache::getSearchMap()
{
    return _search_map;
}

list<pair<string, string>> & SubLRUCache::getLRUCacheContent()
{
    return _LRUCache_content;
}
