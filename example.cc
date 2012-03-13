#include <stdexcept>

#include "testing.h"

// This is equivalent to main()
BEGIN_TEST()
	int a = 0, b = 0;
	std::string test = "bbb";

	// Passes
	EXPECT_TRUE(a == b);

	// Fails
	EXPECT_TRUE(a + 1 == a);

	// Passes
	EXPECT_STRING(test, "bbb");

	// Fails
	EXPECT_STRING(test, "aaa");

	// Passes
	EXPECT_INT(1+2, 3);

	// Fails
	EXPECT_INT(1+1, 1);

	// Passes
	EXPECT_EXCEPTION(throw std::runtime_error("test"), std::exception);

	// Fails
	EXPECT_EXCEPTION(a = b, std::exception);

	// Passes
	EXPECT_NO_EXCEPTION(a = b);

	// Fails
	EXPECT_NO_EXCEPTION(throw std::runtime_error("test"));

// Returns number of failed tests
END_TEST()
