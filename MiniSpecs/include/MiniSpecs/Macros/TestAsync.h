#pragma once

#include "../DSL/MINISPECS_TEST_ASYNC.h"

#define TestAsync(textDescription) MINISPECS_TEST_ASYNC(textDescription, __FILE__, __LINE__)
