#pragma once

#include "Core/_MINISPECS_RUN_CODE_ON_INIT.h"

#define MINISPECS_RUN_CODE_ON_INIT \
    _MINISPECS_RUN_CODE_ON_INIT(_MiniSpecs_RunCodeOnInit_, __COUNTER__)
