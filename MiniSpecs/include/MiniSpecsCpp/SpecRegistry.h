#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

namespace MiniSpecsCpp {

    class SpecRegistry {
        std::unordered_map<std::string, std::function<void()>> _tests;

    public:
        static SpecRegistry& instance() {
            static SpecRegistry instance;
            return instance;
        }

        void add_test(std::string name, std::function<void()> test) {
            std::cout << "Adding test: " << name << std::endl;
            _tests[name] = test;
        }

        void run_all_tests() {
            for (auto& test : _tests) {
                test.second();
            }
        }
    };
}