#include <stdexcept>

#include "testing.h"

// Functions to test
bool is_everything_ok() { return true; }
bool is_everything_ok_fails() { return false; }

std::string get_aaa() { return "aaa"; }
std::string get_aaa_fails() { return "bbb"; }

int get_ten() { return 10; }
int get_ten_fails() { return 11; }

float get_pi() { return 3.141592654; }
float get_pi_fails() { return 2.7182818284; }

void throw_something() { throw std::runtime_error("Foo"); }
void throw_something_fails() { }

void dont_throw() { }
void dont_throw_fails1() { throw std::runtime_error("Foo"); }
void dont_throw_fails2() { throw 42; }

// This is equivalent to main()
BEGIN_TEST()
	std::cerr << "Here you see a sample set of passing and failing tests:" << std::endl;

	// Passes
	EXPECT_TRUE(is_everything_ok());

	// Fails
	EXPECT_TRUE(is_everything_ok_fails());

	// Passes
	EXPECT_STRING(get_aaa(), "aaa");

	// Fails
	EXPECT_STRING(get_aaa_fails(), "aaa");

	// Passes
	EXPECT_INT(get_ten(), 10);

	// Fails
	EXPECT_INT(get_ten_fails(), 10);

	// Passes
	EXPECT_FLOAT_IN_RANGE(get_pi(), 3.14f, 3.15f);

	// Fails
	EXPECT_FLOAT_IN_RANGE(get_pi_fails(), 3.14f, 3.15f);

	// Passes
	EXPECT_EXCEPTION(throw_something(), std::runtime_error);

	// Fails
	EXPECT_EXCEPTION(throw_something_fails(), std::runtime_error);

	// Passes
	EXPECT_NO_EXCEPTION(dont_throw());

	// Fails
	EXPECT_NO_EXCEPTION(dont_throw_fails1());
	EXPECT_NO_EXCEPTION(dont_throw_fails2());

// Returns number of failed tests
END_TEST()
