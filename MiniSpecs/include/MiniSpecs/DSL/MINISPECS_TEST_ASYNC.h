#pragma once

#include "Core/_MINISPECS_TEST_ASYNC.h"

#define MINISPECS_TEST_ASYNC(testDescription) \
    _MINISPECS_TEST_ASYNC(testDescription, _MiniSpecs_Test_Async_, __COUNTER__)
