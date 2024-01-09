#include <MiniSpecs>

#define _MiniSpecs_Concat(a, b) a##b

#define _MiniSpecs_TestDefinitionAndRegistration(textDescription, count)                    \
    void                         _MiniSpecs_Concat(_MiniSpec_Test_, count)();               \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_Concat(_MiniSpec_FunctionRunner_, count)([]() { \
        MiniSpecsCpp::SpecRegistry::instance().add_test(                                    \
            textDescription, _MiniSpecs_Concat(_MiniSpec_Test_, count)                      \
        );                                                                                  \
    });                                                                                     \
    void                         _MiniSpecs_Concat(_MiniSpec_Test_, count)()

#define Test(textDescription) _MiniSpecs_TestDefinitionAndRegistration(textDescription, __COUNTER__)

Test("Some cool test") {
    std::cout << "Hello, OMG we used a macro to define this test!" << std::endl;
}

Test("second test") { std::cout << "Hello, OMG Second!" << std::endl; }
