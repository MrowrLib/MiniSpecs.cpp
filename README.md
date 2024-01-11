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

# TODO

- [ ] OneTimeSetup and OneTimeTeardown
- [ ] OneTimeSetupAsync and OneTimeTeardownAsync
- [ ] CMake/vcpkg demo
- [ ] xmake/xrepo demo
