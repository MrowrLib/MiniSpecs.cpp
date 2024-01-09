#pragma once

#include "FunctionRunner.h"
#include "SpecRegistry.h"

#ifdef SPEC_FILE
    #define _MiniSpecs_CompilationUnitID SPEC_FILE
#else
    #define _MiniSpecs_CompilationUnitID DefaultMiniSpecsCompilationUnit
#endif

#define _MiniSpecs_Concat_Simple(a, b) a##b
#define _MiniSpecs_Concat(a, b) _MiniSpecs_Concat_Simple(a, b)

#define _MiniSpecs_ConcatWithCompilationUnitID(prefix) \
    _MiniSpecs_Concat(prefix, _MiniSpecs_CompilationUnitID)

#define _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(prefix, count) \
    _MiniSpecs_ConcatWithCompilationUnitID(_MiniSpecs_Concat(prefix, count))

#define _MiniSpecs_TestDefinitionAndRegistration(textDescription, count)             \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)(); \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(   \
        _MiniSpec_FunctionRunner_, count                                             \
    )([]() {                                                                         \
        MiniSpecsCpp::SpecRegistry::instance().add_test(                             \
            textDescription,                                                         \
            _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count) \
        );                                                                           \
    });                                                                              \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)()

#define Test(textDescription) _MiniSpecs_TestDefinitionAndRegistration(textDescription, __COUNTER__)
