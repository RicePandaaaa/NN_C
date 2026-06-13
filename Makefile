CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -Iinclude

SRC = src/matrix.c
TEST = tests/test_matrix.c

test_matrix: $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o test_matrix

clean:
	rm -f test_matrix

valgrind: test_matrix
	valgrind --leak-check=full ./test_matrix