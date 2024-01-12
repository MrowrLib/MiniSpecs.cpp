#pragma once

#include "_/SpecRunnerContext.h"

namespace MiniSpecs {

    struct CurrentContext {
        static SpecRunnerContext& get() {
            static SpecRunnerContext context;
            return context;
        }
    };
}