#define SPEC_GROUP Tests1

#include "TestHelper.h"

SetupAsync {
    // ....
    done();
}

TeardownAsync {
    // ....
    done();
}

TestAsync("An async test") {
    // ....
    done();
}
