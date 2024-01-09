#pragma once

#include <functional>
#include <string>
#include <vector>

#include "SpecGroup.h"

namespace MiniSpecsCpp {

    class SpecRegistry {
        std::vector<SpecGroup> _spec_groups;
        SpecGroup*             _current_spec_group;

    public:
        static SpecRegistry& instance() {
            static SpecRegistry instance;
            return instance;
        }

        std::vector<SpecGroup>& spec_groups() { return _spec_groups; }

        SpecGroup* current_spec_group() {
            if (!_current_spec_group) {
                _spec_groups.emplace_back();
                _current_spec_group = &_spec_groups.back();
            }
            return _current_spec_group;
        }

        void add_test(std::string name, std::function<void()> test) {
            current_spec_group()->specs.emplace_back(Spec{name, test});
        }

        void add_setup(std::function<void()> setup) {
            current_spec_group()->setups.emplace_back(Setup{setup});
        }

        void add_teardown(std::function<void()> teardown) {
            current_spec_group()->teardowns.emplace_back(Teardown{teardown});
        }
    };
}