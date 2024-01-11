#pragma once

#include <functional>
#include <memory>

#include "SpecDone.h"

namespace MiniSpecs {

    class Runnable {
        bool                                           _skip           = false;
        bool                                           _is_async       = false;
        std::unique_ptr<std::function<void()>>         _function       = nullptr;
        std::unique_ptr<std::function<void(SpecDone)>> _async_function = nullptr;

    public:
        Runnable(std::function<void()> test_body_function)
            : _function(std::unique_ptr<std::function<void()>>(
                  new std::function<void()>(test_body_function)
              )) {}

        Runnable(std::function<void(SpecDone)> async_test_body_function)
            : _is_async(true),
              _async_function(std::unique_ptr<std::function<void(SpecDone)>>(
                  new std::function<void(SpecDone)>(async_test_body_function)
              )) {}

        bool is_async() const { return _is_async; }
        bool should_skip() const { return _skip; }
        void skip(bool value = true) { _skip = value; }

        void operator()(SpecDone* done = nullptr) {
            if (_is_async) (*_async_function)(*done);
            else (*_function)();
        }
    };
}