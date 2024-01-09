#pragma once

#include <functional>

namespace MiniSpecsCpp {

    struct Teardown {
        std::function<void()> body_function;
    };
}