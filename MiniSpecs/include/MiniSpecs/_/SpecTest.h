#pragma once

#include <string>

#include "Runnable.h"

namespace MiniSpecs {

    class SpecTest : public Runnable {
        std::string  _name;
        std::string  _file_path;
        unsigned int _line_number;

    public:
        SpecTest(
            std::string name, std::string file_path, unsigned int line_number,
            std::function<void()> function
        )
            : Runnable(function), _name(name), _file_path(file_path), _line_number(line_number) {}
        SpecTest(
            std::string name, std::string file_path, unsigned int line_number,
            std::function<void(SpecDone)> function
        )
            : Runnable(function), _name(name), _file_path(file_path), _line_number(line_number) {}

        std::string  name() const { return _name; }
        std::string  file_path() const { return _file_path; }
        unsigned int line_number() const { return _line_number; }
    };
}