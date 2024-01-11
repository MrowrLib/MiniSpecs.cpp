#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_SETUP_ASYNC(symbol, count)                                                                       \
    void                                                                                                            \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_ASYNC_), count)(        \
            MiniSpecs::SpecDone done                                                                                \
        );                                                                                                          \
    MiniSpecs::FunctionRunner                                                                                       \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_ASYNC_RUNNER_), count)( \
            []() {                                                                                                  \
                MiniSpecs::SpecRegistry::instance().add_setup(                                                      \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                              \
                        __MiniSpecs_Concat(symbol, _SETUP_ASYNC_), count                                            \
                    )                                                                                               \
                );                                                                                                  \
            }                                                                                                       \
        );                                                                                                          \
    void                                                                                                            \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_ASYNC_), count)(            \
        MiniSpecs::SpecDone done                                                                                    \
    )
