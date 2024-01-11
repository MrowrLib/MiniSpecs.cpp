<img src="Resources/Images/eyeglasses-35598_1280.png" align="right" width=100>

# MiniSpecs.cpp

> Mini C++ Test Framework

## What?

Simple, beautiful, incredibly easy to write and read tests for `C++11` and beyond!

```cpp
#define SPEC_GROUP My_Tests
 
#include <MiniSpecs/Main.h> // includes main()
#include <MiniSpecs.h>      // includes MiniSpecs
 
Setup    { /* Setup Code */ }
Teardown { /* Teardown Code */ }
 
Test("Some thing") {
    AssertThat(69, Equals(420));
}

TestAsync("Slow thing") {
    // Do something slow...
    done();
}
```

# Table of Contents

- [MiniSpecs.cpp](#minispecscpp)
  - [What?](#what)
- [Table of Contents](#table-of-contents)
- [Installation](#installation)
  - [xmake](#xmake)
    - [`xmake.lua`](#xmakelua)
  - [vcpkg](#vcpkg)
    - [`CMakeLists.txt`](#cmakeliststxt)
    - [`vcpkg.json`](#vcpkgjson)
    - [`vcpkg-configuration.json`](#vcpkg-configurationjson)
- [Why?](#why)
- [Getting Started](#getting-started)
- [Command Line Options](#command-line-options)
- [License](#license)


# Installation

## xmake

### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("minispec")

target("MyTests")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("minispec")
```

## vcpkg

### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find minispec and link it to your target
find_package(minispec CONFIG REQUIRED)
target_link_libraries(Example PRIVATE minispec::minispec)
```

### `vcpkg.json`

```json
{
    "dependencies": ["minispec"]
}
```

### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "TODO"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "TODO",
            "packages": ["minispec"]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

# Why?

I already started writing [Specs.cpp](https://specs.tools), which I hope to finish one day.

But, I haven't finished it! And I **need** a test framework for my projects!

This is a syntax that I **adore** (_and the DSL is **completely configurable!**_)

It checks all of the fantastic boxes for me:

> - [x] Easy to write
> - [x] Easy to read
> - [x] Easy to run
> - [x] Supports async tests

_I like it, and I hope you do too!_

# Getting Started

...

# Command Line Options

```
MiniSpecs: 0.1.0 by Mrowr Purr

Usage: MyTests.exe [options]

Options:
  -t, --timeout        <ms>      Set timeout in milliseconds (default: 5000)
  -i, --include        <name>    Run only specs containing text in the spec/group name
  -e, --exclude        <name>    Skip specs containing text in the spec/group name
  -I, --include-regex  <pattern> Run only specs with spec/group name matching the regular expression
  -E, --exclude-regex  <pattern> Skip specs with spec/group name matching the regular expression
  -h, --help           Show this help
  -v, --version        Show version
```

# License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
