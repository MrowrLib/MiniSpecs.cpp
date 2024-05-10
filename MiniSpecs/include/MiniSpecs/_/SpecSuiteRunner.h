#pragma once

#include <future>
#include <iostream>
#include <regex>
#include <vector>

#include "../Version.h"
#include "SpecDefinitions.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
#endif

namespace MiniSpecs {

    class SpecSuiteRunner {
        SpecDefinitions&         _registry;
        unsigned int             _timeout_ms      = 5000;
        bool                     _only_list_tests = false;
        std::string              _file_path_to_run;
        std::string              _group_name_to_run;
        unsigned int             _line_number_to_run;
        std::vector<std::string> _include_filters;
        std::vector<std::string> _exclude_filters;
        std::vector<std::string> _include_regex_filters;
        std::vector<std::string> _exclude_regex_filters;

        bool is_excluded(const std::string& name) {
            if (!_exclude_filters.empty()) {
                for (auto& filter : _exclude_filters)
                    if (name.find(filter) != std::string::npos) return true;
            }

            if (!_exclude_regex_filters.empty()) {
                for (auto& filter : _exclude_regex_filters)
                    if (std::regex_match(name, std::regex(filter))) return true;
            }

            return false;
        }

        bool passes_include_filters(const std::string& name) {
            if (!_include_filters.empty()) {
                bool passes = false;
                for (auto& filter : _include_filters)
                    if (name.find(filter) != std::string::npos) {
                        passes = true;
                        break;
                    }
                if (!passes) return false;
            }

            if (!_include_regex_filters.empty()) {
                bool passes = false;
                for (auto& filter : _include_regex_filters)
                    if (std::regex_match(name, std::regex(filter))) {
                        passes = true;
                        break;
                    }
                if (!passes) return false;
            }

            return true;
        }

        bool should_run(const SpecTest& spec) {
            if (!_file_path_to_run.empty()) {
                if (spec.file_path() != _file_path_to_run) return false;
                if (_line_number_to_run != 0 && spec.line_number() != _line_number_to_run)
                    return false;
            }
            return !is_excluded(spec.name()) && passes_include_filters(spec.name());
        }

        bool only_print_test_output() const { return !_file_path_to_run.empty(); }

        std::string run(Runnable& runnable) {
            std::string errorMessage;
            try {
                if (runnable.is_async()) {
                    std::promise<void> promise;
                    std::future<void>  future = promise.get_future();
                    auto               done   = SpecDone(promise);
                    runnable(&done);
                    if (future.wait_for(std::chrono::milliseconds(_timeout_ms)) ==
                        std::future_status::timeout) {
                        errorMessage = "Timeout";
                    }
                } else runnable();
#if __has_include(<snowhouse/snowhouse.h>)
            } catch (const snowhouse::AssertionException& e) {
                errorMessage = e.what() + std::string(" (") + e.file() + std::string(":") +
                               std::to_string(e.line()) + std::string(")");
#endif
            } catch (const char* e) {
                errorMessage = e;
            } catch (const std::exception& e) {
                errorMessage = e.what();
            } catch (...) {
                errorMessage = "Unknown exception";
            }
            return errorMessage;
        }

        std::string run_setups(std::vector<Runnable>& setups) {
            std::string errorMessage;
            for (auto& setup : setups) {
                errorMessage = run(setup);
                if (!errorMessage.empty()) break;
            }
            return errorMessage;
        }

        std::vector<std::string> run_teardowns(std::vector<Runnable>& teardowns) {
            std::vector<std::string> errorMessages;
            for (auto& teardown : teardowns) errorMessages.emplace_back(run(teardown));
            return errorMessages;
        }

        constexpr static auto COLOR_NORMAL          = "0";
        constexpr static auto COLOR_FAIL            = "31";
        constexpr static auto COLOR_PASS            = "32";
        constexpr static auto COLOR_FAILURE_MESSAGE = "33";
        constexpr static auto COLOR_GROUP_NAME      = "34";
        constexpr static auto COLOR_SPEC_NAME       = "36";
        constexpr static auto COLOR_NOT_RUN         = "35";  // try 37

        void print_color(const std::string& text, const std::string& color) {
            std::cout << "\033[" << color << "m" << text << "\033[0m";
        }

        void print_color(std::vector<std::string> textParts, const std::string& color) {
            std::cout << "\033[" << color << "m";
            for (auto& textPart : textParts) std::cout << textPart;
            std::cout << "\033[0m";
        }

        void print(const std::string& text) { std::cout << text; }

        void print(std::vector<std::string> textParts) {
            for (auto& textPart : textParts) std::cout << textPart;
        }

        void print_spec_result(
            const std::string& specName, const std::string& errorMessage,
            const std::vector<std::string>& teardownErrorMessages
        ) {
            if (only_print_test_output()) {
                if (!errorMessage.empty() ||
                    std::any_of(
                        teardownErrorMessages.begin(), teardownErrorMessages.end(),
                        [](const std::string& s) { return !s.empty(); }
                    )) {
                    if (!errorMessage.empty()) print(errorMessage + "\n");
                    for (auto& teardownErrorMessage : teardownErrorMessages)
                        if (!teardownErrorMessage.empty()) print(teardownErrorMessage + "\n");
                } else {
                    print_color({"  Passed: ", specName, "\n"}, COLOR_PASS);
                }
                return;
            }

            if (!errorMessage.empty() ||
                std::any_of(
                    teardownErrorMessages.begin(), teardownErrorMessages.end(),
                    [](const std::string& s) { return !s.empty(); }
                )) {
                print_color({"  Failed: ", specName, "\n"}, COLOR_FAIL);
                if (!errorMessage.empty())
                    print_color({"  ", errorMessage, "\n"}, COLOR_FAILURE_MESSAGE);
                for (auto& teardownErrorMessage : teardownErrorMessages)
                    if (!teardownErrorMessage.empty())
                        print_color({"  ", teardownErrorMessage, "\n"}, COLOR_FAILURE_MESSAGE);
            } else {
                print_color({"  Passed: ", specName, "\n"}, COLOR_PASS);
            }
        }

        void print_suite_results(
            unsigned int passed_count, unsigned int failed_count, unsigned int skipped_count
        ) {
            print("\n");
            if (failed_count > 0) print_color("Failed", COLOR_FAIL);
            else if (passed_count > 0) print_color("Passed", COLOR_PASS);
            else print_color("No tests run", COLOR_NOT_RUN);
            print_color(":", COLOR_NORMAL);
            if (passed_count > 0)
                print_color({" ", std::to_string(passed_count), " passed"}, COLOR_PASS);
            if (passed_count > 0 && failed_count > 0) print_color(",", COLOR_NORMAL);
            if (failed_count > 0)
                print_color({" ", std::to_string(failed_count), " failed"}, COLOR_FAIL);
            if ((passed_count > 0 || failed_count > 0) && skipped_count > 0)
                print_color(",", COLOR_NORMAL);
            if (skipped_count > 0)
                print_color({" ", std::to_string(skipped_count), " skipped"}, COLOR_NOT_RUN);
            print_color(".\n", COLOR_NORMAL);
        }

        void parse_args(int argc, char** argv) {
            for (int i = 1; i < argc; i++) {
                std::string arg = argv[i];
                if (arg == "--list" || arg == "-l") {
                    _only_list_tests = true;
                } else if (arg == "--file" || arg == "-f") {
                    if (i + 1 < argc) {
                        _file_path_to_run = argv[i + 1];
                        i++;
                    }
                } else if (arg == "--line" || arg == "-n") {
                    if (i + 1 < argc) {
                        _line_number_to_run = std::stoi(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--timeout" || arg == "-t") {
                    if (i + 1 < argc) {
                        _timeout_ms = std::stoi(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--include" || arg == "-i") {
                    if (i + 1 < argc) {
                        _include_filters.push_back(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--exclude" || arg == "-e") {
                    if (i + 1 < argc) {
                        _exclude_filters.push_back(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--include-regex" || arg == "-I") {
                    if (i + 1 < argc) {
                        _include_regex_filters.push_back(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--exclude-regex" || arg == "-E") {
                    if (i + 1 < argc) {
                        _exclude_regex_filters.push_back(argv[i + 1]);
                        i++;
                    }
                } else if (arg == "--version" || arg == "-v") {
                    print({"MiniSpecs: ", Version::get(), " by Mrowr Purr\n"});
                    exit(0);
                } else if (arg == "--help" || arg == "-h") {
                    print(
                        {"MiniSpecs: ", Version::get(), " by Mrowr Purr\n\n", "Usage: ", argv[0],
                         " [options]\n\n", "Options:\n",
                         "  -t, --timeout        <ms>      Set timeout in milliseconds (default: ",
                         std::to_string(_timeout_ms), ")\n",
                         "  -i, --include        <name>    Run only specs containing text in the spec/group name\n",
                         "  -e, --exclude        <name>    Skip specs containing text in the spec/group name\n",
                         "  -I, --include-regex  <pattern> Run only specs with spec/group name matching the regular expression\n",
                         "  -E, --exclude-regex  <pattern> Skip specs with spec/group name matching the regular expression\n",
                         "  -h, --help           Show this help\n",
                         "  -v, --version        Show version\n"}
                    );
                    exit(0);
                }
            }
        }

        void list_tests() {
            for (auto& group : _registry.spec_groups()) {
                for (auto& spec : group.specs()) {
                    print(
                        spec.file_path() + ":" + std::to_string(spec.line_number()) + " " +
                        group.name() + " > " + spec.name() + "\n"
                    );
                }
            }
        }

    public:
        SpecSuiteRunner(SpecDefinitions& registry) : _registry(registry) {}

        int run(int argc, char** argv) {
            // parse_args(argc, argv);

            if (argc == 3) {
                argc = 5;
                std::vector<std::string> string_args{argv[0], "--file", argv[1], "--line", argv[2]};
                argv = new char*[5];
                for (int i = 0; i < 5; i++) {
                    argv[i] = new char[string_args[i].size() + 1];
                    strcpy(argv[i], string_args[i].c_str());
                }
                parse_args(argc, argv);
            } else {
                parse_args(argc, argv);
            }

            if (_only_list_tests) {
                list_tests();
                return 0;
            }

            unsigned int passed_count  = 0;
            unsigned int failed_count  = 0;
            unsigned int skipped_count = 0;

            for (auto& group : _registry.spec_groups()) {
                bool should_skip_group = group.should_skip() || is_excluded(group.name());
                auto group_color       = should_skip_group ? COLOR_NOT_RUN : COLOR_GROUP_NAME;
                if (should_skip_group && !only_print_test_output())
                    print_color("[SKIP] ", COLOR_NOT_RUN);
                if (!group.name().empty() && !only_print_test_output())
                    print_color({"[" + group.name() + "]\n"}, group_color);

                std::string oneTimeSetupsErrorMessage;
                if (!should_skip_group)
                    oneTimeSetupsErrorMessage = run_setups(group.one_time_setups());

                for (auto& spec : group.specs()) {
                    std::string specNameWithGroup = group.name() + " " + spec.name();
                    bool        should_skip_spec =
                        should_skip_group || spec.should_skip() || !should_run(spec);
                    auto spec_color = should_skip_spec ? COLOR_NOT_RUN : COLOR_SPEC_NAME;
                    if (should_skip_spec && !only_print_test_output())
                        print_color("[SKIP] ", COLOR_NOT_RUN);
                    if (!only_print_test_output())
                        print_color({"> ", spec.name(), "\n"}, spec_color);
                    if (should_skip_spec) {
                        skipped_count++;
                        continue;
                    }

                    // Did the one time setup fail? If so, we fail (and re-use the same message)
                    if (!oneTimeSetupsErrorMessage.empty()) {
                        print_spec_result(spec.name(), oneTimeSetupsErrorMessage, {});
                        failed_count++;
                        continue;
                    }

                    // Setup
                    auto errorMessage = run_setups(group.setups());

                    // Spec
                    if (errorMessage.empty()) errorMessage = run(spec);

                    // Teardown
                    auto teardownErrorMessages = run_teardowns(group.teardowns());

                    // Spec result output
                    print_spec_result(spec.name(), errorMessage, teardownErrorMessages);

                    // Count result
                    if (errorMessage.empty() &&
                        std::all_of(
                            teardownErrorMessages.begin(), teardownErrorMessages.end(),
                            [](const std::string& s) { return s.empty(); }
                        )) {
                        passed_count++;
                    } else {
                        failed_count++;
                    }
                }

                // One time teardowns (note: the tests have ALREADY been run, this can NOT cause any
                // tests to fail)
                auto oneTimeTeardownErrorMessages = run_teardowns(group.one_time_teardowns());
                for (auto& oneTimeTeardownErrorMessage : oneTimeTeardownErrorMessages) {
                    if (!oneTimeTeardownErrorMessage.empty()) {
                        print_color("Error:\n", COLOR_FAIL);
                        print_color(
                            {"  ", oneTimeTeardownErrorMessage, "\n"}, COLOR_FAILURE_MESSAGE
                        );
                    }
                }
            }
            if (!only_print_test_output())
                print_suite_results(passed_count, failed_count, skipped_count);

            if (!_file_path_to_run.empty() && passed_count == 0 && failed_count == 0) {
                if (skipped_count > 0) print("All tests skipped\n");
                else {
                    print("No tests found.");
                    return 1;
                }
            }

            return failed_count > 0 ? 1 : 0;
        }
    };
}