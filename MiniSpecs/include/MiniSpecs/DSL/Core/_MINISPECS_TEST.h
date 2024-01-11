#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_TEST(testDescription, symbol, count)                                                      \
    void                                                                                                     \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_), count)(        \
        );                                                                                                   \
    MiniSpecs::FunctionRunner                                                                                \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_RUNNER_), count)( \
            []() {                                                                                           \
                MiniSpecs::SpecRegistry::instance().add_spec(                                                \
                    testDescription, __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                      \
                                         __MiniSpecs_Concat(symbol, _TEST_), count                           \
                                     )                                                                       \
                );                                                                                           \
            }                                                                                                \
        );                                                                                                   \
    void                                                                                                     \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEST_), count)()
