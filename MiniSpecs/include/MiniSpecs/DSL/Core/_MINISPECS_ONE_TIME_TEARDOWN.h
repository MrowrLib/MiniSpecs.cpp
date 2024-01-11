#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_ONE_TIME_TEARDOWN(symbol, count)                                                                       \
    void                                                                                                                  \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_), count)(        \
        );                                                                                                                \
    MiniSpecs::FunctionRunner                                                                                             \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_RUNNER_), count)( \
            []() {                                                                                                        \
                MiniSpecs::SpecRegistry::instance().add_one_time_teardown(                                                \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                                    \
                        __MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_), count                                            \
                    )                                                                                                     \
                );                                                                                                        \
            }                                                                                                             \
        );                                                                                                                \
    void                                                                                                                  \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_), count)(            \
    )
