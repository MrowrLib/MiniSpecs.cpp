#pragma once

#include "../DSL/Core/_MINISPECS_TEST_ASYNC.h"

#define ExampleAsync(textDescription)                                                    \
    _MINISPECS_TEST_ASYNC(                                                               \
        textDescription, __FILE__, __LINE__, _MiniSpecs_Example_Test_Async_, __COUNTER__ \
    )
