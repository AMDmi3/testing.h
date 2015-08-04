CXX?=		g++
CXXFLAGS?=	#empty
CXXFLAGS+=	-std=c++11 -Wall -Wextra -pedantic -Werror

all: rundemo

rundemo: demo
	./demo || true

checkdemo: demo
	./demo > actual-demo-output.txt 2>&1 || true
	diff -u actual-demo-output.txt expected-demo-output.txt || (echo "Demo output differs from excepted"; false)

updatedemo: demo
	./demo > expected-demo-output.txt 2>&1 || true

demo: demo.cc testing.h
	${CXX} ${CXXFLAGS} demo.cc -o demo

clean:
	rm -f demo actual-demo-output.txt
