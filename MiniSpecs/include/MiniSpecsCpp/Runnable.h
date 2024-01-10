#pragma once

#include <functional>
#include <memory>

#include "Done.h"

namespace MiniSpecsCpp {

    class Runnable {
        bool                                       _is_async       = false;
        std::unique_ptr<std::function<void()>>     _function       = nullptr;
        std::unique_ptr<std::function<void(Done)>> _async_function = nullptr;

    public:
        Runnable(std::function<void()> test_body_function)
            : _function(std::unique_ptr<std::function<void()>>(
                  new std::function<void()>(test_body_function)
              )) {}

        Runnable(std::function<void(Done)> async_test_body_function)
            : _is_async(true),
              _async_function(std::unique_ptr<std::function<void(Done)>>(
                  new std::function<void(Done)>(async_test_body_function)
              )) {}

        bool is_async() const { return _is_async; }

        void operator()(Done* done = nullptr) {
            if (_is_async) (*_async_function)(*done);
            else (*_function)();
        }
    };
}