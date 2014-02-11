CXX?=		g++
CXXFLAGS?=	#empty
CXXFLAGS+=	-std=c++11 -Wall -Wextra -pedantic -Werror

all: example
	./example

example: example.cc testing.h
	${CXX} ${CXXFLAGS} example.cc -o example

clean:
	rm -f example
