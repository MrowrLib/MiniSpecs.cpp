#pragma once

#include "../DSL/Core/_MINISPECS_TEST.h"

#define Spec(textDescription) \
    _MINISPECS_TEST(textDescription, __FILE__, __LINE__, _MiniSpecs_Spec_Test_, __COUNTER__)
