#define SPEC_GROUP Tests2

#include "TestHelper.h"

Setup { cout << "B Setup 1" << endl; }
Setup { cout << "B Setup 2" << endl; }

Teardown { cout << "B Teardown 1" << endl; }
Teardown { cout << "B Teardown 2" << endl; }

Test("Test 1") { cout << "B RUN Test 1" << endl; }
Test("Test 2") { cout << "B RUN Test 2" << endl; }
