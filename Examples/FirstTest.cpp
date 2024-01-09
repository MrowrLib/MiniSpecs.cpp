#define SPEC_FILE FirstTest

#include "TestHelper.h"

Test("This should fail") { AssertThat(69, Equals(420)); }

Test("This should fail too") { throw "KABOOM"; }

Test("This should also fail") { throw std::runtime_error("std Kaboom"); }
