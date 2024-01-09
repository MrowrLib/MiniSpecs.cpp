#define SPEC_GROUP Tests1

#include "TestHelper.h"

Setup { cout << "111 Setup 1" << endl; }
Teardown { cout << "111 Teardown 1" << endl; }
Test("Test 1") { cout << "111 RUN Test 1" << endl; }

Group("C");

Setup { cout << "C Setup 1" << endl; }
Teardown { cout << "C Teardown 1" << endl; }
Test("Test 1") { cout << "C RUN Test 1" << endl; }
