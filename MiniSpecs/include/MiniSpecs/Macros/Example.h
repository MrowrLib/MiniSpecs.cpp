#pragma once

#include "../DSL/Core/_MINISPECS_TEST.h"

#define Example(textDescription) _MINISPECS_TEST(textDescription, _MiniSpecs_Example_Test_, __COUNTER__)
