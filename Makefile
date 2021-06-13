.PHONY: test clean

test: test-thrd test-addr
	./test-addr
	./test-thrd

clean:
	rm -f ./test-thrd ./test-addr

test-thrd: test.cpp std/experimental/future
	g++-7 -I./std -std=c++17 -Wall -Wextra -Werror -O3 -o $@ ./test.cpp -fsanitize=thread -pthread 2>&1

test-addr: test.cpp std/experimental/future
	g++-7 -I./std -std=c++17 -Wall -Wextra -Werror -O3 -o $@ ./test.cpp -fsanitize=address -pthread 2>&1
