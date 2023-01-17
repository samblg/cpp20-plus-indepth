export module ips.cache:loader;

import <string>;

namespace ips::cache {
    export class CacheLoader {
    public:
        CacheLoader(const std::string& basePath) :
            _basePath(basePath) {}

        bool loadCacheFile(const std::string& key, std::string* cacheFileData) {
            return false;
        }

    private:
        std::string _basePath;
    };
}