#pragma once

#include "Core/_MINISPECS_DECLARE_GROUP.h"

#define MINISPECS_DECLARE_GROUP(groupName) \
    _MINISPECS_DECLARE_GROUP(groupName, _MiniSpecs_DeclareGroup_, __COUNTER__)
