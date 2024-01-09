#pragma once

#include <functional>
#include <string>

namespace MiniSpecsCpp {

    struct Spec {
        std::string           name;
        std::function<void()> test_body_function;
    };
}