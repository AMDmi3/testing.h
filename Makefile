CXX?=		g++
CXXFLAGS?=	#empty
CXXFLAGS+=	-std=c++11 -Wall -Wextra -pedantic -Werror

all: demo
	-./demo

demo: demo.cc testing.h
	${CXX} ${CXXFLAGS} demo.cc -o demo

clean:
	rm -f demo
