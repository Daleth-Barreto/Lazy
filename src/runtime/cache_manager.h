/*
 * LazyA Cache Manager - Header (Stub)
 */

#ifndef LAZYA_CACHE_MANAGER_H
#define LAZYA_CACHE_MANAGER_H

#include <string>

namespace lazya {

class CacheManager {
public:
    CacheManager();
    ~CacheManager();
    
    // Cache operations (stubs)
    bool has_cached(const std::string& key);
    bool load_from_cache(const std::string& key);
    bool save_to_cache(const std::string& key, const void* data, size_t size);
    
private:
    std::string cache_dir;
};

} // namespace lazya

#endif // LAZYA_CACHE_MANAGER_H
