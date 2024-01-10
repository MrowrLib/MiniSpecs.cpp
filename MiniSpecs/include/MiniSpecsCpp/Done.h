#pragma once

#include <future>

namespace MiniSpecsCpp {

    class Done {
        std::promise<void>& _promise;

    public:
        Done(std::promise<void>& promise) : _promise(promise) {}

        void operator()() const { _promise.set_value(); }
    };
}