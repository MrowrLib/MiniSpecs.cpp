#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_TEST_ASYNC(testDescription, symbol, count)                                                      \
    void                                                                                                           \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_ASYNC_), count)(        \
            MiniSpecs::SpecDone done                                                                               \
        );                                                                                                         \
    MiniSpecs::FunctionRunner                                                                                      \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_ASYNC_RUNNER_), count)( \
            []() {                                                                                                 \
                MiniSpecs::SpecRegistry::instance().add_spec(                                                      \
                    testDescription, __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                            \
                                         __MiniSpecs_Concat(symbol, _TEST_ASYNC_), count                           \
                                     )                                                                             \
                );                                                                                                 \
            }                                                                                                      \
        );                                                                                                         \
    void                                                                                                           \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_ASYNC_), count)(            \
        MiniSpecs::SpecDone done                                                                                   \
    )
