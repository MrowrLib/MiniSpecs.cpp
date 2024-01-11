#pragma once

#include "Runnable.h"

namespace MiniSpecs {

    class SpecTeardown : public Runnable {
    public:
        SpecTeardown(std::function<void()> function) : Runnable(function) {}
        SpecTeardown(std::function<void(SpecDone)> function) : Runnable(function) {}
    };
}