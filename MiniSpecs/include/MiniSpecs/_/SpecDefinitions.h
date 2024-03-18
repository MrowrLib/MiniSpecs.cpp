#pragma once

#include <functional>
#include <string>
#include <vector>

#include "SpecDone.h"
#include "SpecGroup.h"

namespace MiniSpecs {

    class SpecDefinitions {
        std::vector<SpecGroup> _spec_groups;
        SpecGroup*             _current_spec_group;
        bool                   _skip_next = false;

        bool should_skip_next() {
            bool result = _skip_next;
            _skip_next  = false;
            return result;
        }

    public:
        static SpecDefinitions& instance() {
            static SpecDefinitions instance;
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

        void add_spec(
            std::string name, std::string file_path, unsigned int line_number,
            std::function<void()> fn
        ) {
            auto& spec = current_spec_group()->add_spec(name, file_path, line_number, fn);
            if (should_skip_next()) spec.skip();
        }

        void add_spec(
            std::string name, std::string file_path, unsigned int line_number,
            std::function<void(SpecDone done)> fn
        ) {
            auto& spec = current_spec_group()->add_spec(name, file_path, line_number, fn);
            if (should_skip_next()) spec.skip();
        }

        void add_setup(std::function<void()> fn) {
            auto& setup = current_spec_group()->add_setup(fn);
            if (should_skip_next()) setup.skip();
        }

        void add_setup(std::function<void(SpecDone done)> fn) {
            auto& setup = current_spec_group()->add_setup(fn);
            if (should_skip_next()) setup.skip();
        }

        void add_one_time_setup(std::function<void()> fn) {
            auto& setup = current_spec_group()->add_one_time_setup(fn);
            if (should_skip_next()) setup.skip();
        }

        void add_one_time_setup(std::function<void(SpecDone done)> fn) {
            auto& setup = current_spec_group()->add_one_time_setup(fn);
            if (should_skip_next()) setup.skip();
        }

        void add_teardown(std::function<void()> fn) {
            auto& teardown = current_spec_group()->add_teardown(fn);
            if (should_skip_next()) teardown.skip();
        }

        void add_teardown(std::function<void(SpecDone done)> fn) {
            auto& teardown = current_spec_group()->add_teardown(fn);
            if (should_skip_next()) teardown.skip();
        }

        void add_one_time_teardown(std::function<void()> fn) {
            auto& teardown = current_spec_group()->add_one_time_teardown(fn);
            if (should_skip_next()) teardown.skip();
        }

        void add_one_time_teardown(std::function<void(SpecDone done)> fn) {
            auto& teardown = current_spec_group()->add_one_time_teardown(fn);
            if (should_skip_next()) teardown.skip();
        }

        void add_group(std::string name) {
            _spec_groups.emplace_back(SpecGroup{name});
            _current_spec_group = &_spec_groups.back();
            if (should_skip_next()) _current_spec_group->skip();
        }

        void skip_next() { _skip_next = true; }
    };
}