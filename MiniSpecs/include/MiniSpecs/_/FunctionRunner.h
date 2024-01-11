#pragma once

#include <functional>

namespace MiniSpecs {

    struct FunctionRunner {
        FunctionRunner(std::function<void()> function) { function(); }
    };
}