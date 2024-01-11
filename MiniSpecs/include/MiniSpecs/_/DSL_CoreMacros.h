#pragma once

#include "FunctionRunner.h"  // IWYU pragma: keep
#include "SpecRegistry.h"    // IWYU pragma: keep

#define __MiniSpecs_Stringize_Simple(symbol) #symbol
#define __MiniSpecs_Stringize(symbol) __MiniSpecs_Stringize_Simple(symbol)

#define __MiniSpecs_Concat_Simple(a, b) a##b
#define __MiniSpecs_Concat(a, b) __MiniSpecs_Concat_Simple(a, b)

#define __MiniSpecs_ConcatWithCompilationUnitID(prefix) \
    __MiniSpecs_Concat(prefix, _MiniSpecs_CompilationUnitID)

#define __MiniSpecs_ConcatWithCompilationUnitIDAndCounter(prefix, count) \
    __MiniSpecs_ConcatWithCompilationUnitID(__MiniSpecs_Concat(prefix, count))
