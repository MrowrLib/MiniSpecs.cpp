#pragma once

#include <snowhouse/snowhouse.h>

#include <MiniSpecs>

#if __cplusplus >= 201703L
    #include <assert.hpp>
    #define assert_that(...) VERIFY(__VA_ARGS__)
#endif

using namespace std;
using namespace snowhouse;
