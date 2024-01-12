#pragma once

#include "../../_/DSL_CoreMacros.h"

#define _MINISPECS_SETUP(symbol, count)                                                                       \
    void                                                                                                      \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_), count)(        \
        );                                                                                                    \
    MiniSpecs::FunctionRunner                                                                                 \
        __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_RUNNER_), count)( \
            []() {                                                                                            \
                MiniSpecs::SpecDefinitions::instance().add_setup(                                             \
                    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                                        \
                        __MiniSpecs_Concat(symbol, _SETUP_), count                                            \
                    )                                                                                         \
                );                                                                                            \
            }                                                                                                 \
        );                                                                                                    \
    void                                                                                                      \
    __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(__MiniSpecs_Concat(symbol, _SETUP_), count)(            \
    )
