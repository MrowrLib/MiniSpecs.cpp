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

        constexpr static auto COLOR_RED    = "31";
        constexpr static auto COLOR_GREEN  = "32";
        constexpr static auto COLOR_YELLOW = "33";
        constexpr static auto COLOR_BLUE   = "34";
        constexpr static auto COLOR_PURPLE = "35";
        constexpr static auto COLOR_CYAN   = "36";

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
            unsigned int passed_count = 0;
            unsigned int failed_count = 0;
            for (auto& group : _registry.spec_groups()) {
                if (!group.name.empty()) print_color({"[" + group.name + "]\n"}, COLOR_BLUE);
                for (auto& spec : group.specs) {
                    print_color({"> ", spec.name(), "\n"}, COLOR_CYAN);
                    auto errorMessage = run_setups(group.setups);
                    if (errorMessage.empty()) errorMessage = run(spec);
                    auto teardownErrorMessages = run_teardowns(group.teardowns);
                    if (!errorMessage.empty() ||
                        std::any_of(
                            teardownErrorMessages.begin(), teardownErrorMessages.end(),
                            [](const std::string& s) { return !s.empty(); }
                        )) {
                        print_color({"  Failed: ", spec.name(), "\n"}, COLOR_RED);
                        if (!errorMessage.empty())
                            print_color({"  ", errorMessage, "\n"}, COLOR_YELLOW);
                        for (auto& teardownErrorMessage : teardownErrorMessages)
                            if (!teardownErrorMessage.empty())
                                print_color({"  ", teardownErrorMessage, "\n"}, COLOR_YELLOW);
                        failed_count++;
                    } else {
                        print_color({"  Passed: ", spec.name(), "\n"}, COLOR_GREEN);
                        passed_count++;
                    }
                }
            }
            std::cout << std::endl;
            if (failed_count > 0)
                print_color(
                    {"Failed ", std::to_string(failed_count), " of ",
                     std::to_string(passed_count + failed_count), "\n"},
                    COLOR_RED
                );
            else
                print_color(
                    {"Passed ", std::to_string(passed_count), " of ",
                     std::to_string(passed_count + failed_count), "\n"},
                    COLOR_GREEN
                );
        }
    };
}