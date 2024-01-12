#pragma once

#include <string>

namespace MiniSpecs {

    class Version {
    public:
        static const char* major() { return "0"; }
        static const char* minor() { return "1"; }
        static const char* patch() { return "0"; }
        static std::string get() { return std::string(major()) + "." + minor() + "." + patch(); }
    };
}