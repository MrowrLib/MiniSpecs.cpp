#define SPEC_GROUP Tests1

#include "TestHelper.h"

Setup {}
Teardown {}
Test("Test 1") { AssertThat(1, Equals(2)); }

Group("C");

Setup {}
Teardown {}
Test("Test 1") { throw "BOOM!"; }
