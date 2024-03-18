#pragma once

#include "Core/_MINISPECS_TEST.h"

#define MINISPECS_TEST(testDescription, filepath, linenumber) \
    _MINISPECS_TEST(testDescription, filepath, linenumber, _MiniSpecs_Test_, __COUNTER__)
