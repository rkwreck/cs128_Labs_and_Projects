CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -O0 -gdwarf-4

driver: bin/driver
tests: bin/tests
driver-full: bin/driver-full

bin/driver: ./src/driver.cc ./includes/word_guess_functions.hpp ./src/word_guess_functions.cc ./includes/word_guess_constants.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/word_guess_functions.cc -o $@

bin/tests: ./tests/tests.cc ./includes/word_guess_functions.hpp ./src/word_guess_functions.cc ./includes/word_guess_constants.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/word_guess_functions.cc  -o $@

bin/driver-full: ./src/driver_full.cc ./includes/word_guess_functions.hpp ./src/word_guess_functions.cc ./includes/word_guess_constants.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver_full.cc ./src/word_guess_functions.cc -o $@



.DEFAULT_GOAL := driver
.PHONY: driver tests

clean:
	rm -rf bin/*
