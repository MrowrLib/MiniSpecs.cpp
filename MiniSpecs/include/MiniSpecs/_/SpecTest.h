#pragma once

#include <string>

#include "Runnable.h"

namespace MiniSpecs {

    class SpecTest : public Runnable {
        std::string _name;

    public:
        SpecTest(std::string name, std::function<void()> function)
            : Runnable(function), _name(name) {}
        SpecTest(std::string name, std::function<void(SpecDone)> function)
            : Runnable(function), _name(name) {}

        std::string name() const { return _name; }
    };
}