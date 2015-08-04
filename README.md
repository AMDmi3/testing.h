# testing.h #

This is a simple C++11 unit test frame work.

## Features ##

* Single header file, no dependencies
* Provides detailed information of which expressions are tested and test results
* Colored output

To use this in your project, you may just grab testing.h and add it to
your source tree.

## Short example ##

```c++
#include "testing.h"

BEGIN_TEST()
    EXPECT_TRUE(MyFunc() == "foo");
    EXPECT_EQUAL(GetSomeStr(), "ExpectedString");
    EXPECT_EXCEPTION(MyFunc(), std::runtime_error);
END_TEST()
```

Possible output:

```
PASS: MyFunc() == "foo"
FAIL: MyFunc() returned "UnexpectedString" while expected "ExpectedString"
FAIL: MyFunc() hasn't thrown expected exception std::runtime_error
```

## Longer example ##

See [demo.cc](demo.cc), which demonstrates almost all framework abilities. You
may compile and run the demo by calling ```make```.

## License ##

2-clause BSD, see [COPYING](COPYING) or source files.

## Author ##

Dmitry Marakasov <amdmi3@amdmi3.ru>

## Contributors ##

* [Vladimir Gamalian](https://github.com/vladimirgamalian)
