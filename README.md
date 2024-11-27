<img src="Resources/Images/specs.png" align="right" width=150>

### `MiniSpecs.h` <!-- omit from toc -->

> Mini C++ Test Framework

### What? <!-- omit from toc -->

Simple, easy to write and read tests for `C++11` and beyond!

```cpp
#define SPEC_NAME My_Tests

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

### Why? <!-- omit from toc -->

I already started writing [Specs.cpp](https://specs.tools), which I hope to finish one day.

But, I haven't finished it! And I **need** a test framework for my projects!

This is a syntax that I **adore** (_and the DSL is **completely configurable!**_)

It checks all of the fantastic boxes for me:

- ✔️ Fun to write
- ✔️ Easy to read
- ✔️ Easy to run
- ✔️ Supports async tests

_I like it, and I hope you do too!_

> _Note: MiniSpecs is intentionally simple._
>
> _For example, you cannot write your own test runners or reporters._

# Table of Contents <!-- omit from toc -->

- [Installation](#installation)
  - [xmake](#xmake)
    - [`xmake.lua`](#xmakelua)
  - [vcpkg](#vcpkg)
    - [`CMakeLists.txt`](#cmakeliststxt)
    - [`vcpkg.json`](#vcpkgjson)
    - [`vcpkg-configuration.json`](#vcpkg-configurationjson)
- [Setup a test project](#setup-a-test-project)
  - [Main Entrypoint](#main-entrypoint)
- [Test Groups](#test-groups)
  - [`SPEC_NAME`](#spec_name)
- [Tests](#tests)
  - [Async Tests](#async-tests)
  - [Skipping Tests](#skipping-tests)
- [Test Assertions](#test-assertions)
- [Setup and Teardown](#setup-and-teardown)
  - [Async Setup and Teardown](#async-setup-and-teardown)
- [Running Tests](#running-tests)
- [Syntax Reference](#syntax-reference)
- [License](#license)


# Installation

## xmake

### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("minispecs")
add_requires("vcpkg::snowhouse") -- optional, recommended assertion library

target("Tests")
    set_kind("binary")
    add_packages("minispecs")
    add_packages("vcpkg::snowhouse") -- optional, recommended assertion library
    add_files("*.cpp")
```

## vcpkg

### `CMakeLists.txt`

```cmake
add_executable(Tests main.cpp)

# Add your test .cpp files

# Find minispecs and link it to your target
find_package(minispecs CONFIG REQUIRED)
target_link_libraries(Tests PRIVATE minispecs::minispecs)

# Optional, recommended assertion library
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
```

### `vcpkg.json`

```json
{
    "dependencies": ["minispecs", "snowhouse"]
}
```

### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "a1212c93cabaa9c5c36c1ffdb4bddd59fdf31e43"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "8fd12f83281514368f637d6204eee24a58b47ebe",
            "packages": ["minispecs"]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

# Setup a test project

Test projects should be configured as executable/binary targets.

> See the [Installation](#installation) section for how to setup a test project.

## Main Entrypoint

Every test project needs a `main.cpp` file to run the tests.

```cpp
// main.cpp
#include <MiniSpecs/Main.h>
```

# Test Groups

Groups of tests can be defined in their own `.cpp` files.

## `SPEC_NAME`

A `SPEC_NAME` must be defined before `<MiniSpecs.h>` providing a unique name for the group of tests.

> `SPEC_NAME` can not contain spaces or special characters.
>
> _Any underscores will be removed from the name when presented._

```cpp
#define SPEC_NAME Some_Tests

#include <MiniSpecs.h>

Test("Something...") {
    // ...
}
```

```cpp
#define SPEC_NAME Some_Different_Tests

#include <MiniSpecs.h>

Test("Something else...") {
    // ...
}
```

# Tests

Test are written using either the `Test` or `TestAsync` macros.

```cpp
#define SPEC_NAME My_Tests

#include <MiniSpecs.h>

Test("Some test") {
    // ... Test Code ...
}
```

## Async Tests

Tests for asyncronous code can be written using the `TestAsync` macro.

```cpp
TestAsync("Some test") {
    // ... Test Asyncronous Code ...

    // You must call done() or a timeout will occur
    // The default timeout is 5000ms but can be changed with the -t flag
    done();
}
```

## Skipping Tests

If you want to skip a test, you can use the `Skip` macro.

```cpp
Skip Test("Test Description") {
    // ... Test Code ...
}
```

Skipped tests won't be run and will be reported as skipped.

# Test Assertions

By default, all C++ exceptions are caught and reported as test failures.

```cpp
Test("Kaboom!") {
    // Throw a std::exception
    throw std::runtime_error("Kaboom!");

    // Or simply throw a literal string
    throw "Kaboom!";
}
```

I recommend using the [Snowhouse](https://github.com/banditcpp/snowhouse) assertion library for more expressive tests.

> Snowhouse support C++11 and beyond.
>
> It is available on [vcpkg](https://github.com/microsoft/vcpkg) for easy installation.

```cpp
#define SPEC_NAME Some_Tests

#include <MiniSpecs.h>
#include <snowhouse/snowhouse.h>

using namespace snowhouse;

Test("Some thing") {
    AssertThat(69, Equals(420));
}
```

MiniSpecs has special support for displaying Snowhouse assertion failures.

# Setup and Teardown

Setup and Teardown code can be defined using the `Setup` and `Teardown` macros.

```cpp
#define SPEC_NAME My_Tests

#include <MiniSpecs.h>

Setup {
    // Setup Code
    // This runs before each test
    // Note: an exception in the setup code will cause the test to fail
}

Teardown {
    // Teardown Code
    // This runs after each test (even if the test fails)
}

Test("Some test") {
    // ...
}

Test("Another test") {
    // ...
}
```

If you need to run setup code only once before the tests in a file, you can use the `SetupOnce` macro.

```cpp
SetupOnce {
    // Setup Code
    // This runs once before all tests in the file
    // Note: an exception in the setup code will cause all tests to fail
}
```

If you need to run teardown code only once after the tests in a file, you can use the `TeardownOnce` macro.

```cpp
TeardownOnce {
    // Teardown Code
    // This runs once after all tests in the file
}
```

## Async Setup and Teardown

All of the setup and teardown macros have async versions.

- `SetupAsync`
- `TeardownAsync`
- `SetupOnceAsync`
- `TeardownOnceAsync`

Just like `TestAsync`, you must call `done()` to signal the completion of the async setup or teardown.

# Running Tests

To run the tests, run your defined test project.

By default, all tests are run, but filters are available to run only specific tests.

```
MiniSpecs

Usage: Tests.exe [options]

Options:
  -t, --timeout        <ms>      Set timeout in milliseconds (default: 5000)
  -i, --include        <name>    Run only specs containing text in the spec/group name
  -e, --exclude        <name>    Skip specs containing text in the spec/group name
  -I, --include-regex  <pattern> Run only specs with spec/group name matching the regular expression
  -E, --exclude-regex  <pattern> Skip specs with spec/group name matching the regular expression
  -h, --help           Show this help
  -v, --version        Show version
```

# Syntax Reference

| Code                               | Description                                                                                     |
| ---------------------------------- | ----------------------------------------------------------------------------------------------- |
| `#define SPEC_NAME Name`           | Define the name of the test group<br>Must be unique and contain no spaces or special characters |
| `#include <MiniSpecs/Main.h>`      | Include the main entrypoint for the test project<br>Only put this in one `.cpp` file            |
| `#include <MiniSpecs.h>`           | Include the MiniSpecs test framework<br>Include this in every test file                         |
| `Setup { ... }`                    | Define setup code to run before each test                                                       |
| `SetupAsync { ... }`               | Define async setup code to run before each test                                                 |
| `SetupOnce { ... }`                | Define setup code to run once before all tests in the file                                      |
| `SetupOnceAsync { ... }`           | Define async setup code to run once before all tests in the file                                |
| `Teardown { ... }`                 | Define teardown code to run after each test                                                     |
| `TeardownAsync { ... }`            | Define async teardown code to run after each test                                               |
| `TeardownOnce { ... }`             | Define teardown code to run once after all tests in the file                                    |
| `TeardownOnceAsync { ... }`        | Define async teardown code to run once after all tests in the file                              |
| `Test("Description") { ... }`      | Define a test with a description                                                                |
| `TestAsync("Description") { ... }` | Define an async test with a description                                                         |

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
