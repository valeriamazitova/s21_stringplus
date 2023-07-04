.PHONY: all clean test

NAME = s21__string
CC = gcc -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = s21_string.c s21_sprintf.c s21_sscanf.c dopfunk.c
OBJECT = s21_string.o s21_sprintf.o s21_sscanf.o dopfunk.o
LINUXFLAGS = -lsubunit -lrt -lpthread -lm
LIBS= -lcheck
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 TEST_FLAGS = $(LIBS)
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 TEST_FLAGS =-lpthread  $(LIBS) -pthread -lrt -lm -lsubunit
endif

all: s21_string.a

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_string.a: s21_string.o
	$(CC) -c $(SOURSES)
	@ar rcs s21_string.a $(OBJECT)

test: unit_test.c s21_string.a
ifeq ($(OS), Darwin)
	$(CC) unit_test.c s21_string.a -o unit_test  $(LIBS)
else
	$(CC) unit_test.c s21_string.a -o unit_test  $(LIBS) $(LINUXFLAGS)
endif
	./unit_test

gcov_report: s21_string.a
	@gcc $(GCOVFLAGS) unit_test.c  $(LIBS) $(SOURSES) $(TEST_FLAGS) -o s21_gcov_report
	@./s21_gcov_report
	@lcov -t "s21_gcov_report" -o s21_gcov_report.info -c -d .
	@genhtml -o report s21_gcov_report.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./s21_gcov_report.*  

all_checks: valcheck leak clang

valcheck: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) unit_test.c s21_string.a -o unit_test $(LIBS)
	valgrind --leak-check=full -s ./unit_test
else
	$(CC) unit_test.c s21_string.a -o unit_test $(LIBS) $(LINUX)
	valgrind --leak-check=full -s ./unit_test
endif

leak: s21_string.a
	@$(CC) unit_test.c s21_string.a $(TEST_FLAGS)
	@CK_FORK=no leaks --atExit -- ./a.out

clang:
	cp ../materials/linters/.clang-format . 
	clang-format -n *.c *.h

rebuild: clean all

clean:
	rm -rf ./*.o ./*.a ./a.out ./s21_gcov_report ./*.gcno ./*.gcda ./report ./*.info ./string_o ./*.dSYM ./unit_test ./CPPLINT*  ./.clang-format ./.DS_Store

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

push: clean
	git add .
	git commit -m 'Abobas'
	git push
