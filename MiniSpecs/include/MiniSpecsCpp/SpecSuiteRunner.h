#pragma once

#include "SpecRegistry.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
#endif

namespace MiniSpecsCpp {

    class SpecSuiteRunner {
        SpecRegistry& _registry;

    public:
        SpecSuiteRunner(SpecRegistry& registry) : _registry(registry) {}

        void run() {
            for (auto& test : _registry.tests()) {
                std::cout << "Running test: " << test.first << std::endl;
                try {
                    test.second();
                    std::cout << "Test passed: " << test.first << std::endl;
#if __has_include(<snowhouse/snowhouse.h>)
                } catch (const snowhouse::AssertionException& e) {
                    std::cout << "Test failed: " << test.first << std::endl;
                    std::cout << e.file() << ":" << e.line() << ": " << e.what() << std::endl;
#endif
                } catch (const char* e) {
                    std::cout << "Test failed: " << test.first << std::endl;
                    std::cout << "    " << e << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Test failed: " << test.first << std::endl;
                    std::cout << "    " << e.what() << std::endl;
                } catch (...) {
                    std::cout << "Test failed: " << test.first << std::endl;
                    std::cout << "    Unknown exception" << std::endl;
                }
            }
        }
    };
}