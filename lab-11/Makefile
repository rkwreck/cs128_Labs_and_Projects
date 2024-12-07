CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always

exec: bin/exec

bin/exec: ./src/driver.cc ./includes/bbt.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc -o $@


.DEFAULT_GOAL := exec
.PHONY: exec

clean:
	rm -rf bin/*


