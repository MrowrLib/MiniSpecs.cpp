#define SPEC_FILE FirstTest

#include "TestHelper.h"

#if __cplusplus >= 201703L
Test("libassert failure") { assert_that(69 == 420); }
#endif

Test("This should fail") { AssertThat(69, Equals(420)); }

Test("This should fail too") { throw "KABOOM"; }

Test("This should also fail") { throw std::runtime_error("std Kaboom"); }
