#pragma once

#include "FunctionRunner.h"
#include "SpecRegistry.h"

#define _MiniSpecs_Stringize_Simple(symbol) #symbol
#define _MiniSpecs_Stringize(symbol) _MiniSpecs_Stringize_Simple(symbol)

#define _MiniSpecs_Concat_Simple(a, b) a##b
#define _MiniSpecs_Concat(a, b) _MiniSpecs_Concat_Simple(a, b)

#define _MiniSpecs_ConcatWithCompilationUnitID(prefix) \
    _MiniSpecs_Concat(prefix, _MiniSpecs_CompilationUnitID)

#define _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(prefix, count) \
    _MiniSpecs_ConcatWithCompilationUnitID(_MiniSpecs_Concat(prefix, count))

#define _MiniSpecs_TestDefinitionAndRegistration(textDescription, count)             \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)(); \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(   \
        _MiniSpec_TestDefinitionFunctionRunner_, count                               \
    )([]() {                                                                         \
        MiniSpecsCpp::SpecRegistry::instance().add_test(                             \
            textDescription,                                                         \
            _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count) \
        );                                                                           \
    });                                                                              \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)()

#define _MiniSpecs_SetupOrTeardownDefinitionAndRegistration(typeSymbol, adderFunction, count) \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)();               \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(            \
        _MiniSpec_SetupOrTeardownDefinitionFunctionRunner_, count                             \
    )([]() {                                                                                  \
        MiniSpecsCpp::SpecRegistry::instance().adderFunction(                                 \
            _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)               \
        );                                                                                    \
    });                                                                                       \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)

#define _MiniSpecs_DefineGroup(name, count)                                        \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter( \
        _MiniSpec_DefineGroupFunctionRunner_, count                                \
    )([]() { MiniSpecsCpp::SpecRegistry::instance().add_group(name); });

#define Test(textDescription) _MiniSpecs_TestDefinitionAndRegistration(textDescription, __COUNTER__)

#define Setup \
    _MiniSpecs_SetupOrTeardownDefinitionAndRegistration(_MiniSpec_Setup_, add_setup, __COUNTER__)()

#define Teardown                                         \
    _MiniSpecs_SetupOrTeardownDefinitionAndRegistration( \
        _MiniSpec_Teardown_, add_teardown, __COUNTER__   \
    )()

#define Group(name) _MiniSpecs_DefineGroup(name, __COUNTER__)

#ifdef SPEC_FILE
    #define _MiniSpecs_CompilationUnitID SPEC_FILE
#elif defined(SPEC_GROUP)
    #define _MiniSpecs_CompilationUnitID SPEC_GROUP
Group(_MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID));
#else
    #define _MiniSpecs_CompilationUnitID DefaultMiniSpecsCompilationUnit
#endif
