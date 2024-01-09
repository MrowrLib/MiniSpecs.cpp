#define SPEC_FILE FirstTest

#include <MiniSpecs>

Test("Some cool test") {
    std::cout << "Hello, OMG we used a macro to define this test!" << std::endl;
}

Test("second test") { std::cout << "Hello, OMG Second!" << std::endl; }
