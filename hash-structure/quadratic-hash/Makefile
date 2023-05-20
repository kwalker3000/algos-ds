
CXX = clang++
CFLAGS = -fsanitize=address -g -Wall

all: test

test: __test__/test.o
	$(CXX) $(CFLAGS) $< -o $@

__test__/test.o: __test__/main.test.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -r *.o *.*~ test __test__/test.o
