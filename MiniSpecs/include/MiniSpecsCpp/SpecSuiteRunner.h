#pragma once

#include <vector>

#include "SpecRegistry.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
#endif

namespace MiniSpecsCpp {

    class SpecSuiteRunner {
        SpecRegistry& _registry;

        std::string run_function(std::function<void()> function) {
            std::string errorMessage;
            try {
                function();
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
                errorMessage = run_function(setup.body_function);
                if (!errorMessage.empty()) break;
            }
            return errorMessage;
        }

        std::vector<std::string> run_teardowns(std::vector<Teardown>& teardowns) {
            std::vector<std::string> errorMessages;
            for (auto& teardown : teardowns)
                errorMessages.emplace_back(run_function(teardown.body_function));
            return errorMessages;
        }

    public:
        SpecSuiteRunner(SpecRegistry& registry) : _registry(registry) {}

        void run() {
            unsigned int passed_count = 0;
            unsigned int failed_count = 0;
            for (auto& group : _registry.spec_groups()) {
                for (auto& spec : group.specs) {
                    std::cout << "Running " << spec.name << std::endl;
                    auto errorMessage = run_setups(group.setups);
                    if (errorMessage.empty()) errorMessage = run_function(spec.test_body_function);
                    auto teardownErrorMessages = run_teardowns(group.teardowns);
                    if (!errorMessage.empty() ||
                        std::any_of(
                            teardownErrorMessages.begin(), teardownErrorMessages.end(),
                            [](const std::string& s) { return !s.empty(); }
                        )) {
                        std::cout << "Failed: " << spec.name << std::endl;
                        if (!errorMessage.empty()) std::cout << "  " << errorMessage << std::endl;
                        for (auto& teardownErrorMessage : teardownErrorMessages)
                            if (!teardownErrorMessage.empty())
                                std::cout << "  " << teardownErrorMessage << std::endl;
                        failed_count++;
                    } else {
                        std::cout << "Passed: " << spec.name << std::endl;
                        passed_count++;
                    }
                }
            }
            std::cout << std::endl;
            if (failed_count > 0)
                std::cout << "Failed " << failed_count << " of " << passed_count + failed_count
                          << std::endl;
            else
                std::cout << "Passed " << passed_count << " of " << passed_count + failed_count
                          << std::endl;
        }
    };
}