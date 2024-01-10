#pragma once

#include "Runnable.h"

namespace MiniSpecsCpp {

    class Teardown : public Runnable {
    public:
        Teardown(std::function<void()> function) : Runnable(function) {}
        Teardown(std::function<void(Done)> function) : Runnable(function) {}
    };
}