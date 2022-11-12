CC=gcc -g
FLAGS= -Wall -Werror -Wextra
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
LIBS_MACOS= -L /usr/local/lib -lcheck

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN=open report.html
LIBS=$(LIBS_MACOS)
# LEAK_CHECK = CK_FORK=no leaks -atExit -- ./s21_test
endif
 
ifeq ($(OS), Linux)
OPEN=lynx
LIBS=$(LIBS_LINUX)
# LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all -s ./test
endif

all: clean test
	$(CC) -g $(FLAGS) my_matrix.c test.c $(LIBS) --coverage
	./a.out

me: clean test
	$(CC) -g $(FLAGS) my_matrix.c my_test.c $(LIBS) --coverage
#	./a.out
test:
	checkmk clean_mode=1 test.check > test.c

my_matrix.a:
	$(CC) -c my_matrix.c
	ar -rcs my_matrix.a my_matrix.o 

my_matrix.o_with_gcov: my_matrix.c  
	$(CC) -c my_matrix.c --coverage

s21_my_matrix.a_with_gcov: my_matrix.o_with_gcov 	
	ar -rcs my_matrix.a my_matrix.o 

gcov_report:
	gcovr --html --html-details -o report.html
	$(OPEN) report.html

cpp:
# cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h




clean:
	rm -f *.out *.gcda *.gcno *.o *.a report.* s21_test test_with_gcov* *.gcov test.c
