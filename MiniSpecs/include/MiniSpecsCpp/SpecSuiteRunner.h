#pragma once

#include <future>
#include <vector>

#include "SpecRegistry.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
#endif

namespace MiniSpecsCpp {

    class SpecSuiteRunner {
        SpecRegistry& _registry;

        std::string run(Runnable& runnable) {
            std::string errorMessage;
            try {
                if (runnable.is_async()) {
                    std::promise<void> promise;
                    std::future<void>  future = promise.get_future();
                    auto               done   = Done(promise);
                    runnable(&done);
                    if (future.wait_for(std::chrono::milliseconds(1000)) ==
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

    public:
        SpecSuiteRunner(SpecRegistry& registry) : _registry(registry) {}

        void run() {
            unsigned int passed_count  = 0;
            unsigned int failed_count  = 0;
            unsigned int skipped_count = 0;
            for (auto& group : _registry.spec_groups()) {
                auto group_color = group.should_skip() ? COLOR_NOT_RUN : COLOR_GROUP_NAME;
                if (group.should_skip()) print_color("[SKIP] ", COLOR_NOT_RUN);
                if (!group.name().empty()) print_color({"[" + group.name() + "]\n"}, group_color);
                for (auto& spec : group.specs()) {
                    bool should_skip = group.should_skip() || spec.should_skip();
                    auto spec_color  = should_skip ? COLOR_NOT_RUN : COLOR_SPEC_NAME;
                    if (should_skip) print_color("[SKIP] ", COLOR_NOT_RUN);
                    print_color({"> ", spec.name(), "\n"}, spec_color);
                    if (group.should_skip() || spec.should_skip()) {
                        skipped_count++;
                        continue;
                    }
                    auto errorMessage = run_setups(group.setups());
                    if (errorMessage.empty()) errorMessage = run(spec);
                    auto teardownErrorMessages = run_teardowns(group.teardowns());
                    if (!errorMessage.empty() ||
                        std::any_of(
                            teardownErrorMessages.begin(), teardownErrorMessages.end(),
                            [](const std::string& s) { return !s.empty(); }
                        )) {
                        print_color({"  Failed: ", spec.name(), "\n"}, COLOR_FAIL);
                        if (!errorMessage.empty())
                            print_color({"  ", errorMessage, "\n"}, COLOR_FAILURE_MESSAGE);
                        for (auto& teardownErrorMessage : teardownErrorMessages)
                            if (!teardownErrorMessage.empty())
                                print_color(
                                    {"  ", teardownErrorMessage, "\n"}, COLOR_FAILURE_MESSAGE
                                );
                        failed_count++;
                    } else {
                        print_color({"  Passed: ", spec.name(), "\n"}, COLOR_PASS);
                        passed_count++;
                    }
                }
            }
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
    };
}