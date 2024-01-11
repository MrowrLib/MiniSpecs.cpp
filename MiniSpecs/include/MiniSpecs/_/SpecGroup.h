#pragma once

#include <vector>

#include "Runnable.h"
#include "SpecTest.h"

namespace MiniSpecs {

    class SpecGroup {
        std::string           _name;
        std::vector<SpecTest> _specs;
        std::vector<Runnable> _setups;
        std::vector<Runnable> _teardowns;
        bool                  _skip = false;

    public:
        SpecGroup(const std::string& name) : _name(name) {}
        SpecGroup() : SpecGroup("") {}

        std::string name() const { return _name; }
        bool        should_skip() const { return _skip; }
        void        skip(bool value = true) { _skip = value; }

        std::vector<SpecTest>& specs() { return _specs; }
        std::vector<Runnable>& setups() { return _setups; }
        std::vector<Runnable>& teardowns() { return _teardowns; }

        SpecTest& add_spec(std::string name, std::function<void()> test) {
            _specs.emplace_back(name, test);
            return _specs.back();
        }

        SpecTest& add_spec(std::string name, std::function<void(SpecDone done)> test) {
            _specs.emplace_back(name, test);
            return _specs.back();
        }

        Runnable& add_setup(std::function<void()> setup) {
            _setups.emplace_back(setup);
            return _setups.back();
        }

        Runnable& add_setup(std::function<void(SpecDone done)> setup) {
            _setups.emplace_back(setup);
            return _setups.back();
        }

        Runnable& add_teardown(std::function<void()> teardown) {
            _teardowns.emplace_back(teardown);
            return _teardowns.back();
        }

        Runnable& add_teardown(std::function<void(SpecDone done)> teardown) {
            _teardowns.emplace_back(teardown);
            return _teardowns.back();
        }
    };
}