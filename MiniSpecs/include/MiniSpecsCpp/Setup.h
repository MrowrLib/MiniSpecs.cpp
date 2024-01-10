#pragma once

#include <functional>

#include "Runnable.h"

namespace MiniSpecsCpp {

    class Setup : public Runnable {
    public:
        Setup(std::function<void()> function) : Runnable(function) {}
        Setup(std::function<void(Done)> function) : Runnable(function) {}
    };
}