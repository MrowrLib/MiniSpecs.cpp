#pragma once

#include "../DSL/Core/_MINISPECS_TEST.h"

#define It(textDescription) _MINISPECS_TEST(textDescription, _MiniSpecs_It_Test_, __COUNTER__)
