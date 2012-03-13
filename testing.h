/*
 * Copyright (c) 2011-2012 Dmitry Marakasov <amdmi3@amdmi3.ru>
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

#include <iostream>
#include <exception>

#define TEST_COLOR

#ifdef TEST_COLOR
#	define PASSED "\e[0;32mPASSED:\e[0m "
#	define FAILED "\e[1;31mFAILED:\e[0m "
#else
#	define PASSED "PASSED: "
#	define FAILED "FAILED: "
#endif

#define BEGIN_TEST() int main() { int ret = 0;

#define END_TEST() if (ret > 0) std::cerr << ret << " failures" << std::endl; return ret; }

#define EXPECT_STRING(expr, expected) { \
		std::string result = (expr); \
		if (result != expected) { \
			std::cerr << FAILED #expr " returned \"" << result << "\", while expected \"" << expected << "\"" << std::endl; ++ret; \
		} else { \
			std::cerr << PASSED #expr " == \"" << expected << "\"" << std::endl; \
		} \
	}

#define EXPECT_TRUE(expr) { \
		if (!(expr)) { \
			std::cerr << FAILED #expr << std::endl; ++ret; \
		} else { \
			std::cerr << PASSED #expr << std::endl; \
		} \
	}

#define EXPECT_EXCEPTION(expr, exception) { \
		bool correct_catch = false; \
		try { \
			expr; \
		} catch (exception &e) { \
			correct_catch = true; \
		} catch (...) { \
		} \
		if (correct_catch) { \
			std::cerr << PASSED "correctly cought " #exception << std::endl; \
		} else { \
			std::cerr << FAILED "didn't catch expected " #exception << std::endl; ++ret; \
		} \
	}

#define EXPECT_NO_EXCEPTION(expr) { \
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
			std::cerr << FAILED "unexpected exception thrown: " << what << std::endl; ++ret; \
		} else if (had_exception) { \
			std::cerr << FAILED "unexpected unknown exception thrown" << std::endl; ++ret; \
		} else { \
			std::cerr << PASSED "no unexpected exceptinos thrown" << std::endl; \
		} \
	}
