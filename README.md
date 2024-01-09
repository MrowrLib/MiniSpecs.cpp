<img src="Resources/Images/eyeglasses-35598_1280.png" align="right" width=100>

# `<MiniSpecs>`

Mini C++ Test Framework

```cpp
#define SPEC_GROUP My_Tests
 
#include <MiniSpecs>
 
Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }
 
Test("Some thing") {
    assert_that(69 == 420);
    AssertThat(69, Equals(420));
}
```
