#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_RUN_CODE_ON_INIT(symbol, count)                                                                        \
    void                                                                                                                  \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _RUN_CODE_ON_INIT_), count)(         \
        );                                                                                                                \
    MiniSpecs::FunctionRunner                                                                                             \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _RUN_CODE_ON_INIT_RUNNER_), count)(  \
            []() {                                                                                                        \
                __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _RUN_CODE_ON_INIT_), count)( \
                );                                                                                                        \
            }                                                                                                             \
        );                                                                                                                \
    void                                                                                                                  \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _RUN_CODE_ON_INIT_), count)(             \
    )
