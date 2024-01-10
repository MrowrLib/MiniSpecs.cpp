<img src="Resources/Images/eyeglasses-35598_1280.png" align="right" width=100>

# `<MiniSpecs>`

> Mini C++ Test Framework

_For `C++11` and beyond!_

```cpp
#define SPEC_GROUP My_Tests
 
#include <MiniSpecs>
 
Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }
 
Test("Some thing") {
    AssertThat(69, Equals(420));
}

TestAsync("Slow thing") {
    // Do something slow...
    done();
}
```

```
MiniSpecs: 0.1.0 by Mrowr Purr

Usage: D:\\Code\\MrowrLib\\MiniSpecs.cpp\\build\\windows\\x64\\debug\\Example Tests C++11.exe [options]

Options:
  -t, --timeout <ms>  Set timeout in milliseconds (default: 5000)
  -i, --include <re>  Run only specs matching the regular expression
  -e, --exclude <re>  Skip specs matching the regular expression
  -I, --include-regex <re>  Run only specs matching the regular expression
  -E, --exclude-regex <re>  Skip specs matching the regular expression
  -h, --help          Show this help
  -v, --version       Show version
```

# TODO

- [ ] CMake/vcpkg demo
- [ ] xmake/xrepo demo