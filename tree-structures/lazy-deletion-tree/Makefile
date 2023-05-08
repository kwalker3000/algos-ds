
CXX = clang++
CLFAGS = -fsanitize=address -g -Wall

main: main.o
	$(CXX) $(CFLAGS) -o $@ $^

test: ./__test__/main.test.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -r *.o *.*~ *~ test ./__test__/main.test.o
