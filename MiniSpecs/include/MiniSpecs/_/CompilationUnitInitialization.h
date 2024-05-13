#pragma once

#ifdef SPEC_NAME

    #define _MiniSpecs_CompilationUnitID SPEC_NAME

    #include "../DSL/Core/_MINISPECS_DECLARE_GROUP.h"

_MINISPECS_DECLARE_GROUP(
    __MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID), true, _MiniSpecs_SPEC_GROUP_Group_,
    __COUNTER__
);

#else
    #define _MiniSpecs_CompilationUnitID DefaultMiniSpecsCompilationUnit
#endif
