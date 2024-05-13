#pragma once

#include "Core/_MINISPECS_DECLARE_GROUP.h"

#define MINISPECS_DECLARE_GROUP(groupName, removeUnderscores) \
    _MINISPECS_DECLARE_GROUP(groupName, removeUnderscores, _MiniSpecs_DeclareGroup_, __COUNTER__)
