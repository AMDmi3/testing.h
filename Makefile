CXX?=		g++
CXXFLAGS?=	#empty

all: example
	./example

example: example.cc testing.h
	${CXX} ${CXXFLAGS} example.cc -o example
