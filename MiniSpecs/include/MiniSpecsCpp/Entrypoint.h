#pragma once

#include "SpecSuiteRunner.h"

int main() {
    MiniSpecsCpp::SpecSuiteRunner(MiniSpecsCpp::SpecRegistry::instance()).run();
    return 0;
}
