#pragma once

#include "../DSL/Core/_MINISPECS_TEST_ASYNC.h"

#define SpecAsync(textDescription) \
    _MINISPECS_TEST_ASYNC(textDescription, _MiniSpecs_Spec_Test_Async_, __COUNTER__)
