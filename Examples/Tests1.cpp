#define SPEC_GROUP Tests1

#include "TestHelper.h"

SetupAsync {
    // ....
    done();
}

TeardownAsync {
    // ....
    // done();
}

// Skip
TestAsync("An async test") {
    // ....
    done();
}

Test("Foo") { throw "BOOM!"; }
Test("Bar") {}
Test("Baz") {}
