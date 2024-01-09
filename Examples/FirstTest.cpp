#include <MiniSpecs>

// Test("Something") {
//     //
//     AssertThat(69, Equals(420));
// }

// void TestSomething() {
//     //
//     // AssertThat(69, Equals(420));
// }

MiniSpecsCpp::FunctionRunner myRunner([]() {
    MiniSpecsCpp::SpecRegistry::instance().add_test("Something Test", []() {
        std::cout << "Hello from the test running!" << std::endl;
    });
});
