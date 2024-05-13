add_requires("vcpkg::snowhouse")

target("Tests")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("MiniSpecs")
    add_packages("vcpkg::snowhouse")

-- TODO: test target for C++17 with libassert
