
CXX = clang++
CFLAGS = -fsanitize=address -g -Wall

main: main.o
	$(CXX) $(CFLAGS) -o $@ $^

test: test.o
	$(CXX) $(CFLAGS) -o $@ $^

test.o: __test__/main.test.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ 

clean:
	rm -r *.o *.*~ *~ test ./__test__/main.test.o
