# TODO

- [ ] `Async` tests
- [ ] CMake/vcpkg demo
- [ ] xmake/xrepo demo
- [ ] Can `Skip` tests
- [ ] Can run only certain tests from CLI
- [ ] Can exclude only certain tests from CLI

---

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
```
