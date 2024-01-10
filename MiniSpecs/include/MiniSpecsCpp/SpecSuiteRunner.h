#pragma once

#include <future>
#include <regex>
#include <vector>

#include "SpecRegistry.h"
#include "Version.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
#endif

namespace MiniSpecsCpp {

    class SpecSuiteRunner {
        SpecRegistry&            _registry;
        unsigned int             _timeout_ms = 5000;
        std::vector<std::string> _include_filters;
        std::vector<std::string> _exclude_filters;
        std::vector<std::string> _include_regex_filters;
        std::vector<std::string> _exclude_regex_filters;

        bool should_run(const std::string& name) {
            if (!_exclude_filters.empty()) {
                for (auto& filter : _exclude_filters)
                    if (name.find(filter) != std::string::npos) return false;
            }
            if (!_exclude_regex_filters.empty()) {
                for (auto& filter : _exclude_regex_filters)
                    if (std::regex_match(name, std::regex(filter))) return false;
            }
            if (!_include_filters.empty()) {
                bool should_run = false;
                for (auto& filter : _include_filters)
                    if (name.find(filter) != std::string::npos) {
                        should_run = true;
                        break;
                    }
                if (!should_run) return false;
            }
            if (!_include_regex_filters.empty()) {
                bool should_run = false;
                for (auto& filter : _include_regex_filters)
                    if (std::regex_match(name, std::regex(filter))) {
                        should_run = true;
                        break;
                    }
                if (!should_run) return false;
            }
            return true;
        }

        std::string run(Runnable& runnable) {
            std::string errorMessage;
            try {
                if (runnable.is_async()) {
                    std::promise<void> promise;
                    std::future<void>  future = promise.get_future();
                    auto               done   = Done(promise);
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

        std::string run_setups(std::vector<Setup>& setups) {
            std::string errorMessage;
            for (auto& setup : setups) {
                errorMessage = run(setup);
                if (!errorMessage.empty()) break;
            }
            return errorMessage;
        }

        std::vector<std::string> run_teardowns(std::vector<Teardown>& teardowns) {
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
                if (arg == "--timeout" || arg == "-t") {
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
                         "  -t, --timeout <ms>  Set timeout in milliseconds (default: 5000)\n",
                         "  -i, --include <re>  Run only specs matching the regular expression\n",
                         "  -e, --exclude <re>  Skip specs matching the regular expression\n",
                         "  -I, --include-regex <re>  Run only specs matching the regular expression\n",
                         "  -E, --exclude-regex <re>  Skip specs matching the regular expression\n",
                         "  -h, --help          Show this help\n",
                         "  -v, --version       Show version\n"}
                    );
                    exit(0);
                }
            }
        }

    public:
        SpecSuiteRunner(SpecRegistry& registry) : _registry(registry) {}

        int run(int argc, char** argv) {
            parse_args(argc, argv);

            unsigned int passed_count  = 0;
            unsigned int failed_count  = 0;
            unsigned int skipped_count = 0;

            for (auto& group : _registry.spec_groups()) {
                bool should_skip_group = group.should_skip() || !should_run(group.name());
                auto group_color       = should_skip_group ? COLOR_NOT_RUN : COLOR_GROUP_NAME;
                if (should_skip_group) print_color("[SKIP] ", COLOR_NOT_RUN);
                if (!group.name().empty()) print_color({"[" + group.name() + "]\n"}, group_color);

                for (auto& spec : group.specs()) {
                    bool should_skip_spec =
                        should_skip_group || spec.should_skip() || !should_run(spec.name());
                    auto spec_color = should_skip_spec ? COLOR_NOT_RUN : COLOR_SPEC_NAME;
                    if (should_skip_spec) print_color("[SKIP] ", COLOR_NOT_RUN);
                    print_color({"> ", spec.name(), "\n"}, spec_color);
                    if (should_skip_spec) {
                        skipped_count++;
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
            }
            print_suite_results(passed_count, failed_count, skipped_count);
            return failed_count > 0 ? 1 : 0;
        }
    };
}