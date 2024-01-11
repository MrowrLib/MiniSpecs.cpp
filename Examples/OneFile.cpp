#define SPEC_GROUP MainGroup

#include <MiniSpecs.h>
#include <MiniSpecs/Main.h>

Configure { std::cout << "Configure" << std::endl; }

Teardown { std::cout << "Teardown" << std::endl; }

Setup { std::cout << "Setup" << std::endl; }

SetupAsync {
    std::cout << "SetupAsync" << std::endl;
    done();
}

TeardownAsync {
    std::cout << "TeardownAsync" << std::endl;
    done();
}

TODO Test("A") { throw "Something!"; }

TestAsync("B") { done(); }

Group("More Tests");

Test("C") { throw "Something!"; }
