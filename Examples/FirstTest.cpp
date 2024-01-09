#include <MiniSpecs>

#define Test(textDescription)                                                             \
    void                         myTestFunction();                                        \
    MiniSpecsCpp::FunctionRunner myRunner([]() {                                          \
        MiniSpecsCpp::SpecRegistry::instance().add_test(textDescription, myTestFunction); \
    });                                                                                   \
    void                         myTestFunction()

Test("Some cool test") {
    std::cout << "Hello, OMG we used a macro to define this test!" << std::endl;
}

// Test("second test") {

// }
