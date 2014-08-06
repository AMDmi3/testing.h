/*
 * Copyright (c) 2011-2013 Dmitry Marakasov <amdmi3@amdmi3.ru>
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

#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include <iostream>
#include <exception>
#include <string>
#include <sstream>

// Define NO_TEST_COLOR before including testing.h to disable colors
#ifndef NO_TEST_COLOR
#	define TEST_COLOR
#endif

#define TEST_ESCAPE "\033"

#ifdef TEST_COLOR
#	define  PASSED TEST_ESCAPE "[0;32m PASSED:" TEST_ESCAPE "[0m "
#	define WARNING TEST_ESCAPE "[1;33mWARNING:" TEST_ESCAPE "[0m "
#	define  FAILED TEST_ESCAPE "[1;31m FAILED:" TEST_ESCAPE "[0m "
#else
#	define  PASSED " PASSED: "
#	define WARNING "WARNING: "
#	define  FAILED " FAILED: "
#endif

template<class T>
std::string QuoteHelper(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template<>
std::string QuoteHelper<std::string>(const std::string& value) {
	return std::string("\"") + value + std::string("\"");
}

std::string DescrHelper(const std::string& descr) {
	if (descr == "")
		return "";

	return std::string(" (") + descr + std::string(")");
}

// Test begin/end
#define BEGIN_TEST(...) \
	int main(__VA_ARGS__) { \
		int num_failing_tests_ = 0; \
		try {

#define HANDLE_EXTRA_EXCEPTION(exception) \
		} catch(exception) { \
			num_failing_tests_++;

#define END_TEST() \
		} catch(std::exception& e) { \
			num_failing_tests_++; \
			std::cerr << "unexpected exception was thrown during the test: " << e.what() << std::endl; \
		} catch (...) { \
			num_failing_tests_++; \
			std::cerr << "unexpected exception was thrown during the test" << std::endl; \
		} \
		if (num_failing_tests_ > 0) \
			std::cerr << num_failing_tests_ << " failures" << std::endl; return num_failing_tests_; \
	}

// Checks
#define EXPECT_TRUE_BASE(expr, descr, fatal) { \
		if (!(expr)) { \
			std::cerr << (fatal ? FAILED : WARNING) << #expr << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} else { \
			std::cerr << PASSED #expr << DescrHelper(descr) << std::endl; \
		} \
	}

#define EXPECT_EQUAL_BASE(expr, expected, descr, fatal) { \
		auto result = (expr); \
		if (result != expected) { \
			std::cerr << (fatal ? FAILED : WARNING) << \
				#expr " returned " << QuoteHelper(result) << ", " \
				"while expected " << QuoteHelper((decltype(result))expected) << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} else { \
			std::cerr << PASSED \
				#expr " == " << QuoteHelper((decltype(result))expected) << DescrHelper(descr) << std::endl; \
		} \
	}

#define EXPECT_IN_RANGE_BASE(expr, from, to, descr, fatal) { \
		auto result = (expr); \
		if (from <= result && result <= to) { \
			std::cerr << PASSED \
				#expr " returned " << QuoteHelper(result) << ", " \
				"which is in range [" << \
					QuoteHelper((decltype(result))from) << ", " << \
					QuoteHelper((decltype(result))to) << \
				"] as expected" << DescrHelper(descr) << std::endl; \
		} else { \
			std::cerr << (fatal ? FAILED : WARNING) << \
				#expr " returned " << QuoteHelper(result) << ", " \
				"which is out of expected range [" << \
					QuoteHelper((decltype(result))from) << ", " << \
					QuoteHelper((decltype(result))to) << \
				"]" << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} \
	}

#define EXPECT_EXCEPTION_BASE(expr, exception, descr, fatal) { \
		bool correct_catch = false; \
		try { \
			expr; \
		} catch (exception &e) { \
			correct_catch = true; \
		} catch (...) { \
		} \
		if (correct_catch) { \
			std::cerr << PASSED #expr " has thrown " #exception << " as expected " << DescrHelper(descr) << std::endl; \
		} else { \
			std::cerr << (fatal ? FAILED : WARNING) << #expr " hasn't thrown expected " #exception << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} \
	}

#define EXPECT_NO_EXCEPTION_BASE(expr, descr, fatal) { \
		bool had_exception = false; \
		const char* what = NULL; \
		try { \
			expr; \
		} catch (std::exception& e) { \
			had_exception = true; \
			what = e.what(); \
		} catch (...) { \
			had_exception = true; \
		} \
		if (had_exception && what) { \
			std::cerr << (fatal ? FAILED : WARNING) << #expr << " has thrown unexpected exception derived from std::exception, what() returned \"" << what << "\"" << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} else if (had_exception) { \
			std::cerr << (fatal ? FAILED : WARNING) << #expr << " has thrown unexpected exception not derived from std::exception" << DescrHelper(descr) << std::endl; \
			num_failing_tests_ += fatal; \
		} else { \
			std::cerr << PASSED #expr << " hasn't thrown any exceptions as expected" << DescrHelper(descr) << std::endl; \
		} \
	}

// Check shortcuts
#define EXPECT_TRUE(expr) EXPECT_TRUE_BASE(expr, "", 1)
#define EXPECT_TRUE_DESCR(expr, descr) EXPECT_TRUE_BASE(expr, descr, 1)
#define EXPECT_TRUE_WARN(expr) EXPECT_TRUE_BASE(expr, "", 0)
#define EXPECT_TRUE_DESCR_WARN(expr, descr) EXPECT_TRUE_BASE(expr, descr, 0)
#define EXPECT_EQUAL(expr, expected) EXPECT_EQUAL_BASE(expr, expected, "", 1)
#define EXPECT_EQUAL_DESCR(expr, expected, descr) EXPECT_EQUAL_BASE(expr, expected, descr, 1)
#define EXPECT_EQUAL_WARN(expr, expected) EXPECT_EQUAL_BASE(expr, expected, "", 0)
#define EXPECT_EQUAL_DESCR_WARN(expr, expected, descr) EXPECT_EQUAL_BASE(expr, expected, descr, 0)
#define EXPECT_IN_RANGE(expr, from, to) EXPECT_IN_RANGE_BASE(expr, from, to, "", 1)
#define EXPECT_IN_RANGE_DESCR(expr, from, to, descr) EXPECT_IN_RANGE_BASE(expr, from, to, descr, 1)
#define EXPECT_IN_RANGE_WARN(expr, from, to) EXPECT_IN_RANGE_BASE(expr, from, to, "", 0)
#define EXPECT_IN_RANGE_DESCR_WARN(expr, from, to, descr) EXPECT_IN_RANGE_BASE(expr, from, to, descr, 0)
#define EXPECT_EXCEPTION(expr, exception) EXPECT_EXCEPTION_BASE(expr, exception, "", 1)
#define EXPECT_EXCEPTION_DESCR(expr, exception, descr) EXPECT_EXCEPTION_BASE(expr, exception, descr, 1)
#define EXPECT_EXCEPTION_WARN(expr, exception) EXPECT_EXCEPTION_BASE(expr, exception, "", 0)
#define EXPECT_EXCEPTION_DESCR_WARN(expr, exception, descr) EXPECT_EXCEPTION_BASE(expr, exception, descr, 0)
#define EXPECT_NO_EXCEPTION(expr) EXPECT_NO_EXCEPTION_BASE(expr, "", 1)
#define EXPECT_NO_EXCEPTION_DESCR(expr, descr) EXPECT_NO_EXCEPTION_BASE(expr, descr, 1)
#define EXPECT_NO_EXCEPTION_WARN(expr) EXPECT_NO_EXCEPTION_BASE(expr, "", 0)
#define EXPECT_NO_EXCEPTION_DESCR_WARN(expr, descr) EXPECT_NO_EXCEPTION_BASE(expr, descr, 0)

#endif // TESTING_H_INCLUDED
