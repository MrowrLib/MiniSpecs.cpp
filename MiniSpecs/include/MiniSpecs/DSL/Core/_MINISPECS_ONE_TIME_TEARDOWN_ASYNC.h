#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_ONE_TIME_TEARDOWN_ASYNC(symbol, count)                                                                       \
    void                                                                                                                        \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_ASYNC_), count)(        \
            MiniSpecs::SpecDone done                                                                                            \
        );                                                                                                                      \
    MiniSpecs::FunctionRunner                                                                                                   \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_ASYNC_RUNNER_), count)( \
            []() {                                                                                                              \
                MiniSpecs::SpecDefinitions::instance().add_one_time_teardown(                                                   \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                                          \
                        __MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_ASYNC_), count                                            \
                    )                                                                                                           \
                );                                                                                                              \
            }                                                                                                                   \
        );                                                                                                                      \
    void                                                                                                                        \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _ONE_TIME_TEARDOWN_ASYNC_), count)(            \
        MiniSpecs::SpecDone done                                                                                                \
    )
