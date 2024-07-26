CC = gcc

SRCMODULES = s21_decimal.c utils.c test_add.c
OBJMODULES = $(SRCMODULES:.c=.o)

CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -L. s21_decimal.a -lm `pkg-config --cflags --libs check`
	
TEST_EXEC = test
REPORT_DIR = ./report

all: clean s21_decimal.a test

s21_decimal.a: $(OBJMODULES)
	ar rcs $@ $^
	ranlib $@

test: clean s21_decimal.a
	$(CC) $(CFLAGS) --coverage main.c -o $(TEST_EXEC) $(SRCMODULES) $(LDFLAGS)
	./$(TEST_EXEC)

gcov_report: test
	lcov -t "$(TEST_EXEC)" --output-file report.info --capture -q --directory ./
	genhtml -o $(REPORT_DIR) report.info

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.a *.gcno *.gcda *.out $(REPORT_DIR)/ report.info $(TEST_EXEC)

format:
	clang-format -i --style=Google *.c *.h