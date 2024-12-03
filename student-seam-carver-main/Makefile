CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always
exec: bin/exec
tests_i: bin/tests_i
tests_ip: bin/tests_ip

bin/exec: ./src/driver.cc ./includes/image_processing.hpp ./includes/image.hpp ./src/image.cc ./src/image_processing.cc ./includes/pixel.hpp ./src/pixel.cc
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/image.cc ./src/pixel.cc ./src/image_processing.cc -o $@

bin/tests_i: ./tests/tests_image.cc ./includes/image.hpp ./src/image.cc ./includes/pixel.hpp ./src/pixel.cc ./includes/tests_helpers.hpp ./src/tests_helpers.cc
	$(CXX) $(CXX_FLAGS) ./tests/tests_image.cc ./src/image.cc ./src/pixel.cc ./src/tests_helpers.cc -o $@

bin/tests_ip: ./tests/tests_image_processing.cc ./includes/image_processing.hpp ./includes/image.hpp ./src/image.cc ./src/image_processing.cc ./includes/pixel.hpp ./src/pixel.cc ./includes/tests_helpers.hpp ./src/tests_helpers.cc
	$(CXX) $(CXX_FLAGS) ./src/tests_helpers.cc ./tests/tests_image_processing.cc ./src/image.cc ./src/pixel.cc ./src/image_processing.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests_i tests_ip

clean:
	rm -rf bin/*
