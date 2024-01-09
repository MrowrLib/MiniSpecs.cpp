#define SPEC_FILE Tests1

#include "TestHelper.h"

Setup { cout << "A Setup 1" << endl; }
Setup { cout << "A Setup 2" << endl; }

Teardown { cout << "A Teardown 1" << endl; }
Teardown { cout << "A Teardown 2" << endl; }

Test("Test 1") { cout << "A RUN Test 1" << endl; }
Test("Test 2") { cout << "A RUN Test 2" << endl; }
