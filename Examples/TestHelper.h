#pragma once

#include <MiniSpecs.h>
#include <snowhouse/snowhouse.h>

#if __cplusplus >= 201703L
    #include <assert.hpp>
    #define assert_that(...) VERIFY(__VA_ARGS__)
#endif

using namespace std;
using namespace snowhouse;
