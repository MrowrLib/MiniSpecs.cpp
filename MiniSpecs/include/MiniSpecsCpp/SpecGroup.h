#pragma once

#include <vector>

#include "Setup.h"
#include "Spec.h"
#include "Teardown.h"

namespace MiniSpecsCpp {

    class SpecGroup {
        std::string           _name;
        std::vector<Spec>     _specs;
        std::vector<Setup>    _setups;
        std::vector<Teardown> _teardowns;
        bool                  _skip = false;

    public:
        SpecGroup(const std::string& name) : _name(name) {}
        SpecGroup() : SpecGroup("") {}

        std::string name() const { return _name; }
        bool        should_skip() const { return _skip; }
        void        skip(bool value = true) { _skip = value; }

        std::vector<Spec>&     specs() { return _specs; }
        std::vector<Setup>&    setups() { return _setups; }
        std::vector<Teardown>& teardowns() { return _teardowns; }

        Spec& add_spec(std::string name, std::function<void()> test) {
            _specs.emplace_back(name, test);
            return _specs.back();
        }

        Spec& add_spec(std::string name, std::function<void(Done done)> test) {
            _specs.emplace_back(name, test);
            return _specs.back();
        }

        Setup& add_setup(std::function<void()> setup) {
            _setups.emplace_back(setup);
            return _setups.back();
        }

        Setup& add_setup(std::function<void(Done done)> setup) {
            _setups.emplace_back(setup);
            return _setups.back();
        }

        Teardown& add_teardown(std::function<void()> teardown) {
            _teardowns.emplace_back(teardown);
            return _teardowns.back();
        }

        Teardown& add_teardown(std::function<void(Done done)> teardown) {
            _teardowns.emplace_back(teardown);
            return _teardowns.back();
        }
    };
}