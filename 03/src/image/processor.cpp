export module ips.image:processor;

import <string>;
import <cstdint>;

namespace ips::image{
    export class Processor {
    public:
        void setWidth(int32_t width) {
            _width = width;
        }

        int32_t getWidth() const {
            return _width;
        }

        void setHeight(int32_t height) {
            _height = height;
        }

        int32_t getHeight() const {
            return _height;
        }

        void setQuality(int32_t quality) {
            _quality = quality;
        }

        int32_t getQuality() const {
            return _quality;
        }

        void setMode(const std::string& mode) {
            _mode = mode;
        }

        const std::string& getMode() const {
            return _mode;
        }

        std::string&& processImage(const std::string& data) {
            return "";
        }

    private:
        int32_t _width;
        int32_t _height;
        int32_t _quality;
        std::string _mode;
    };
}