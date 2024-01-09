add_requires("vcpkg::snowhouse", "libassert_latest")

target("Example Tests C++11")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("MiniSpecs")
    add_packages("vcpkg::snowhouse")

target("Example Tests C++17")
    set_languages("cxx17")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("MiniSpecs")
    add_packages("vcpkg::snowhouse", "libassert_latest")
