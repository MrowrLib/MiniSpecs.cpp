#pragma once

#include "../DSL/Core/_MINISPECS_TEST.h"

#define It(textDescription) \
    _MINISPECS_TEST(textDescription, __FILE__, __LINE__, _MiniSpecs_It_Test_, __COUNTER__)
