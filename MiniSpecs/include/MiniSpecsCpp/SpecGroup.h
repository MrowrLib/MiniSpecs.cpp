#pragma once

#include <vector>

#include "Setup.h"
#include "Spec.h"
#include "Teardown.h"

namespace MiniSpecsCpp {

    struct SpecGroup {
        std::string           name;
        std::vector<Spec>     specs;
        std::vector<Setup>    setups;
        std::vector<Teardown> teardowns;
    };
}