#pragma once

#include "Core/_MINISPECS_TEST.h"

#define MINISPECS_TEST(testDescription) \
    _MINISPECS_TEST(testDescription, _MiniSpecs_Test_, __COUNTER__)
