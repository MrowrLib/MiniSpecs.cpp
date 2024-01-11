#pragma once

#include <functional>

#include "Runnable.h"

namespace MiniSpecs {

    class SpecSetup : public Runnable {
    public:
        SpecSetup(std::function<void()> function) : Runnable(function) {}
        SpecSetup(std::function<void(SpecDone)> function) : Runnable(function) {}
    };
}