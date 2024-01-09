#pragma once

#include <functional>

namespace MiniSpecsCpp {

    struct Setup {
        std::function<void()> body_function;
    };
}