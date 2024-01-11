#pragma once

#include <future>

namespace MiniSpecs {

    class SpecDone {
        std::promise<void>& _promise;

    public:
        SpecDone(std::promise<void>& promise) : _promise(promise) {}

        void operator()() const { _promise.set_value(); }
    };
}