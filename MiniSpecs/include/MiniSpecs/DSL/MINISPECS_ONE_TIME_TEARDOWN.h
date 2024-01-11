#pragma once

#include "Core/_MINISPECS_ONE_TIME_TEARDOWN.h"

#define MINISPECS_ONE_TIME_TEARDOWN \
    _MINISPECS_ONE_TIME_TEARDOWN(_MiniSpecs_One_Time_Teardown_, __COUNTER__)
