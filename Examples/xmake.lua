add_requires("vcpkg::snowhouse")

target("Example Tests")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("MiniSpecs")
    add_packages("vcpkg::snowhouse")
