#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_TEARDOWN(symbol, count)                                                                       \
    void                                                                                                         \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_), count)(        \
        );                                                                                                       \
    MiniSpecs::FunctionRunner                                                                                    \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_RUNNER_), count)( \
            []() {                                                                                               \
                MiniSpecs::SpecDefinitions::instance().add_teardown(                                             \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                           \
                        __MiniSpecs_Concat(symbol, _TEARDOWN_), count                                            \
                    )                                                                                            \
                );                                                                                               \
            }                                                                                                    \
        );                                                                                                       \
    void                                                                                                         \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_), count)(            \
    )
