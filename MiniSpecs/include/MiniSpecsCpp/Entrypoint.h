#pragma once

#include "SpecRegistry.h"

int main() {
    MiniSpecsCpp::SpecRegistry::instance().run_all_tests();
    return 0;
}
