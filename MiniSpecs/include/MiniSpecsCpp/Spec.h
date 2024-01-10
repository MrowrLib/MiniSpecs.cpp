#pragma once

#include <string>

#include "Runnable.h"

namespace MiniSpecsCpp {

    class Spec : public Runnable {
        std::string _name;

    public:
        Spec(std::string name, std::function<void()> function) : Runnable(function), _name(name) {}
        Spec(std::string name, std::function<void(Done)> function)
            : Runnable(function), _name(name) {}

        std::string name() const { return _name; }
    };
}