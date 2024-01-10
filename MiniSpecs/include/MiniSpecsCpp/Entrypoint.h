#pragma once

#include "SpecSuiteRunner.h"

int main(int argc, char** argv) {
    return MiniSpecsCpp::SpecSuiteRunner(MiniSpecsCpp::SpecRegistry::instance()).run(argc, argv);
}
