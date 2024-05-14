#define SPEC_NAME This_is_the_spec_name

#include "TestHelper.h"  // IWYU pragma: keep

TestAsync("An Aync Test - Pass") {
    AssertThat(1, Equals(1));
    done();
}

TestAsync("An Aync Test - Fail") {
    AssertThat(1, Equals(2));
    done();
}
