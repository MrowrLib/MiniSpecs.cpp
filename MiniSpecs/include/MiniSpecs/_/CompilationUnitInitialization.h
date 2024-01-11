#pragma once

// SPEC_FILE: simply alias for CompilationUnitID
#ifdef SPEC_FILE
    #define _MiniSpecs_CompilationUnitID SPEC_FILE

// SPEC_CONTEXT: simply alias for CompilationUnitID
#elif defined(SPEC_CONTEXT)
    #define _MiniSpecs_CompilationUnitID SPEC_CONTEXT

// SPEC_GROUP: alias for CompilationUnitID and declare group
#elif defined(SPEC_GROUP)
    #define _MiniSpecs_CompilationUnitID SPEC_GROUP

    #include "../DSL/Core/_MINISPECS_DECLARE_GROUP.h"

_MINISPECS_DECLARE_GROUP(
    __MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID), _MiniSpecs_SPEC_GROUP_Group_, __COUNTER__
);

// SKIP_SPEC_FILE: alias for CompilationUnitID and and declare group (and skip)
#elif defined(SKIP_SPEC_GROUP)
    #define _MiniSpecs_CompilationUnitID SKIP_SPEC_GROUP

    #include "../DSL/Core/_MINISPECS_DECLARE_GROUP.h"
    #include "../DSL/Core/_MINISPECS_SKIP.h"

_MINISPECS_SKIP(_MiniSpecs_SPEC_GROUP_Skip_, __COUNTER__);
_MINISPECS_DECLARE_GROUP(
    __MiniSpecs_Stringize(_MiniSpecs_CompilationUnitID), _MiniSpecs_SPEC_GROUP_Group_, __COUNTER__
);

// DEFAULT: No #define
#else
    #define _MiniSpecs_CompilationUnitID DefaultMiniSpecsCompilationUnit
#endif
