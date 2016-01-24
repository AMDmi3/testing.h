/*
 * Copyright (c) 2011-2014 Dmitry Marakasov <amdmi3@amdmi3.ru>
 * All rights reserved.
 *
 * See https://github.com/AMDmi3/testing.h for updates, bug reports,
 * forks etc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdexcept>

#include "testing.h"

// Functions to test
bool return_true() { return true; }
bool return_false() { return false; }

std::string return_aaa() { return "aaa"; }

int return_10() { return 10; }

float return_pi() { return 3.141592654f; }

void throw_runtime_error() { throw std::runtime_error("hello, I'm std::runtime_error"); }
void throw_42() { throw 42; }
void throw_nothing() { }

// This is equivalent to main()
BEGIN_TEST()
	// EXPECT_TRUE examples
	std::cerr << std::endl << "You may check boolean expressions:" << std::endl << std::endl << "    ";
	EXPECT_TRUE(return_true());

	std::cerr << "    ";
	EXPECT_TRUE(return_false());

	// EXPECT_EQUAL examples
	std::cerr << std::endl << "Also you may check equality with arbitrary types (note clever quoting):" << std::endl << std::endl << "    ";
	EXPECT_EQUAL(return_aaa(), "aaa");

	std::cerr << "    ";
	EXPECT_EQUAL(return_aaa(), "bbbb");

	std::cerr << "    ";
	EXPECT_EQUAL(return_10(), 10);

	std::cerr << "    ";
	EXPECT_EQUAL(return_10(), 11);

	std::cerr << "    ";
	EXPECT_EQUAL(return_pi(), return_pi());

	std::cerr << "    ";
	EXPECT_EQUAL(return_pi(), 1.2345);

	// EXPECT_EXCEPTION examples
	std::cerr << std::endl << "You may also check for exceptions:" << std::endl << std::endl << "    ";
	EXPECT_EXCEPTION(throw_runtime_error(), std::runtime_error);

	std::cerr << "    ";
	EXPECT_EXCEPTION(throw_runtime_error(), std::logic_error);

	std::cerr << "    ";
	EXPECT_EXCEPTION(throw_42(), std::runtime_error);

	std::cerr << "    ";
	EXPECT_EXCEPTION(throw_nothing(), std::logic_error);

	// EXPECT_NO_EXCEPTION examples
	std::cerr << std::endl << "Any you may check for absence of exceptions:" << std::endl << std::endl << "    ";
	EXPECT_NO_EXCEPTION(throw_runtime_error());

	std::cerr << "    ";
	EXPECT_NO_EXCEPTION(throw_nothing());

	// examples of tuning
	std::cerr << std::endl << "You may add custom descriptions for your checks:" << std::endl << std::endl << "    ";
	EXPECT_TRUE(return_false(), "expression should be true for test to pass");

	std::cerr << std::endl << "...or replace standard messages with them:" << std::endl << std::endl << "    ";
	EXPECT_TRUE(return_false(), "expression should be true for test to pass", HIDE_MESSAGE);

	std::cerr << std::endl << "You may mark a test as non-fatal. If it fails, it's not accounted for total number of failed tests:" << std::endl << std::endl << "    ";
	EXPECT_TRUE(return_false(), NON_FATAL);

	std::cerr << std::endl << "You may permanently enable flags which control test behavior:" << std::endl << std::endl << "    ";
	ENABLE_FLAGS(HIDE_MESSAGE);
	EXPECT_TRUE(false, "only description is displayed");

	std::cerr << "    ";
	ENABLE_FLAGS(NON_FATAL);
	EXPECT_TRUE(false, "and all tests are non-fatal");

	std::cerr << "    ";
	EXPECT_TRUE(false, "this goes on until flags are reset");

	RESET_FLAGS();

	std::cerr << "    ";
	EXPECT_TRUE(false, "back to default behavior");

	std::cerr << std::endl << "If an exception is thrown and it's not handled (e.g. by EXPECT_EXCEPTION or try/catch), the execution is stopped and no more tests are run. There are standard handlers for std::exception, but you may provide handlers for your own exceptions, for example to provide more diagnostic info..." << std::endl << std::endl;

	std::cerr << "(exception is thrown)" << std::endl;
	EXPECT_TRUE((throw_runtime_error(), true));

HANDLE_EXCEPTION(std::runtime_error& e)
	std::cerr << std::endl << "...like this: what() = \"" << e.what() << "\"" << std::endl;

	std::cerr << std::endl << "This concludes the demo." << std::endl;

	std::cerr << std::endl << "In the end, summary is shown:" << std::endl << std::endl << "    ";
END_TEST()
