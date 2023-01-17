export module ips.app;

import <string>;
import <map>;

import ips.network;
import ips.image;
import ips.cache;

namespace ips::app {
    export void processRequest(
        ips::cache::CacheLoader* cacheLoader,
        ips::network::RequestPtr request,
        ips::network::ResponsePtr response
    ) {
        const std::string& path = request->getPath();
        const std::map<std::string, std::string>& query = request->getQuery();
        std::string data = request->getBody();
        ips::image::Processor imageProcessor;
        std::string cacheKey = path;

        auto widthIterator = query.find("width");
        if (widthIterator != query.cend()) {
            imageProcessor.setWidth(std::stoi(widthIterator->second));
            cacheKey += "&width=" + widthIterator->second;
        }

        auto heighIterator = query.find("height");
        if (heighIterator != query.cend()) {
            imageProcessor.setHeight(std::stoi(heighIterator->second));
            cacheKey += "&height=" + heighIterator->second;
        }

        auto qualityIterator = query.find("quality");
        if (qualityIterator != query.cend()) {
            imageProcessor.setQuality(std::stoi(qualityIterator->second));
            cacheKey += "&quality=" + qualityIterator->second;
        }

        auto modeIterator = query.find("mode");
        if (modeIterator != query.cend()) {
            imageProcessor.setMode(modeIterator->second);
            cacheKey += "&mode=" + modeIterator->second;
        }

        std::string processedImageData;
        bool hasCache = cacheLoader->loadCacheFile(cacheKey, &processedImageData);
        if (hasCache) {
            response->send(processedImageData);

            return;
        }

        processedImageData = imageProcessor.processImage(data);
        response->send(processedImageData);
    }
}