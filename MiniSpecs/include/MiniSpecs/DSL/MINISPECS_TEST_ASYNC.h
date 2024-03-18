#pragma once

#include "Core/_MINISPECS_TEST_ASYNC.h"

#define MINISPECS_TEST_ASYNC(testDescription, filepath, linenumber)                \
    _MINISPECS_TEST_ASYNC(                                                         \
        testDescription, filepath, linenumber, _MiniSpecs_Test_Async_, __COUNTER__ \
    )
