#pragma once

#include <functional>

namespace MiniSpecsCpp {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> function) { function(); }
    };
}