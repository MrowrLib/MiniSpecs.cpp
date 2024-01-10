#pragma once

#include "FunctionRunner.h"
#include "SpecRegistry.h"

using SpecDone = MiniSpecsCpp::Done;

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
        MiniSpecsCpp::SpecRegistry::instance().add_spec(                             \
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

#define _MiniSpecs_AsyncSetupOrTeardownDefinitionAndRegistration(typeSymbol, adderFunction, count) \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)(SpecDone done);       \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                 \
        _MiniSpec_SetupOrTeardownDefinitionFunctionRunner_, count                                  \
    )([]() {                                                                                       \
        MiniSpecsCpp::SpecRegistry::instance().adderFunction(                                      \
            _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)                    \
        );                                                                                         \
    });                                                                                            \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(typeSymbol, count)

#define _MiniSpecs_AsyncTestDefinitionAndRegistration(textDescription, count)                     \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)(SpecDone done); \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(                \
        _MiniSpec_TestDefinitionFunctionRunner_, count                                            \
    )([]() {                                                                                      \
        MiniSpecsCpp::SpecRegistry::instance().add_spec(                                          \
            textDescription,                                                                      \
            _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)              \
        );                                                                                        \
    });                                                                                           \
    void _MiniSpecs_ConcatWithCompilationUnitIDAndCounter(_MiniSpec_Test_, count)

#define _MiniSpecs_DefineGroup(symbol, name, count)                                \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter( \
        symbol, count                                                              \
    )([]() { MiniSpecsCpp::SpecRegistry::instance().add_group(name); });

#define _MiniSpecs_Skip(symbol, count)                                             \
    MiniSpecsCpp::FunctionRunner _MiniSpecs_ConcatWithCompilationUnitIDAndCounter( \
        symbol, count                                                              \
    )([]() { MiniSpecsCpp::SpecRegistry::instance().skip_next(); });

#define Test(textDescription) _MiniSpecs_TestDefinitionAndRegistration(textDescription, __COUNTER__)

#define TestAsync(textDescription) \
    _MiniSpecs_AsyncTestDefinitionAndRegistration(textDescription, __COUNTER__)(SpecDone done)

#define Setup \
    _MiniSpecs_SetupOrTeardownDefinitionAndRegistration(_MiniSpec_Setup_, add_setup, __COUNTER__)()

#define SetupAsync                                            \
    _MiniSpecs_AsyncSetupOrTeardownDefinitionAndRegistration( \
        _MiniSpec_Setup_, add_setup, __COUNTER__              \
    )(SpecDone done)

#define Teardown                                         \
    _MiniSpecs_SetupOrTeardownDefinitionAndRegistration( \
        _MiniSpec_Teardown_, add_teardown, __COUNTER__   \
    )()

#define TeardownAsync                                         \
    _MiniSpecs_AsyncSetupOrTeardownDefinitionAndRegistration( \
        _MiniSpec_Teardown_, add_teardown, __COUNTER__        \
    )(SpecDone done)

#define Group(name) _MiniSpecs_DefineGroup(_MiniSpecs_Group_, name, __COUNTER__)

#define Skip _MiniSpecs_Skip(_MiniSpecs_Skip_, __COUNTER__)

#ifdef SPEC_FILE
    #define _MiniSpecs_CompilationUnitID SPEC_FILE
#elif defined(SPEC_GROUP)
    #define _MiniSpecs_CompilationUnitID SPEC_GROUP
_MiniSpecs_DefineGroup(
    _MiniSpecs_TopLevelGroup_, _MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID), __COUNTER__
);
#elif defined(SKIP_SPEC_GROUP)
    #define _MiniSpecs_CompilationUnitID SKIP_SPEC_GROUP
_MiniSpecs_Skip(_MiniSpecs_TopLevelSkip_, __COUNTER__) _MiniSpecs_DefineGroup(
    _MiniSpecs_TopLevelGroup_, _MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID), __COUNTER__
);
#else
    #define _MiniSpecs_CompilationUnitID DefaultMiniSpecsCompilationUnit
#endif
