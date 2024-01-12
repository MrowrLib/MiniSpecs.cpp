#pragma once

#include "SpecSuiteRunner.h"

int main(int argc, char** argv) {
    return MiniSpecs::SpecSuiteRunner(MiniSpecs::SpecDefinitions::instance()).run(argc, argv);
}
