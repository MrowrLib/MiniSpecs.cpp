#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_SKIP(symbol, count)                                                                       \
    MiniSpecs::FunctionRunner                                                                                \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SKIP_RUNNER_), count)( \
            []() { MiniSpecs::SpecDefinitions::instance().skip_next(); }                                     \
        );
