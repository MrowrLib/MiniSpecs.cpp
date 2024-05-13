#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_DECLARE_GROUP(groupName, removeUnderscores, symbol, count)    \
    MiniSpecs::FunctionRunner __MiniSpecs_ConcatWithCompilationUnitIDAndCounter( \
        __MiniSpecs_Concat(symbol, _DECLARE_GROUP_RUNNER_), count                \
    )([]() { MiniSpecs::SpecDefinitions::instance().add_group(groupName, removeUnderscores); });
