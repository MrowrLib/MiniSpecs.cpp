#define SPEC_GROUP MainGroup

#include <MiniSpecs.h>
#include <MiniSpecs/Main.h>

Setup { std::cout << "Setup" << std::endl; }
OneTimeSetup { std::cout << "OneTimeSetup" << std::endl; }
OneTimeTeardown {
    std::cout << "OneTimeTeardown" << std::endl;
    throw "BOOM!";
}
OneTimeTeardown {
    std::cout << "OneTimeTeardown" << std::endl;
    throw "BOOM!";
}

Test("Test 1") {}
Test("Test 2") {}
Test("Test 3") {}
