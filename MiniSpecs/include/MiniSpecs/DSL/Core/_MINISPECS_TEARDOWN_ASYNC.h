#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_TEARDOWN_ASYNC(symbol, count)                                                                       \
    void                                                                                                               \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_ASYNC_), count)(        \
            MiniSpecs::SpecDone done                                                                                   \
        );                                                                                                             \
    MiniSpecs::FunctionRunner                                                                                          \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_ASYNC_RUNNER_), count)( \
            []() {                                                                                                     \
                MiniSpecs::SpecRegistry::instance().add_teardown(                                                      \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                                 \
                        __MiniSpecs_Concat(symbol, _TEARDOWN_ASYNC_), count                                            \
                    )                                                                                                  \
                );                                                                                                     \
            }                                                                                                          \
        );                                                                                                             \
    void                                                                                                               \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _TEARDOWN_ASYNC_), count)(            \
        MiniSpecs::SpecDone done                                                                                       \
    )
