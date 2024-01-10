#pragma once

#include <iostream>

namespace MiniSpecsCpp {

    struct Done {
        void operator()() const { std::cout << "You Called Done!" << std::endl; }
    };
}