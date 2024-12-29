CXX=clang++
CXX_FLAGS=-std=c++20 -lm -lmp3lame -Iincludes -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always


tests: bin/tests

exec: bin/exec

bin/tests: ./tests/tests.cc ./src/motif_node.cc ./includes/motif_node.hpp ./includes/musical_tree.hpp ./src/musical_tree.cc
	$(CXX) $(CXX_FLAGS) ./src/motif_node.cc ./tests/tests.cc ./src/musical_tree.cc -o $@

bin/exec: ./src/driver.cc ./src/musical_tree.cc ./includes/musical_tree.hpp ./src/utilities.cc ./src/motif_node.cc ./includes/motif_node.hpp
	$(CXX) $(CXX_FLAGS) ./src/musical_tree.cc ./src/driver.cc ./src/motif_node.cc ./src/utilities.cc  -o $@


.DEFAULT_GOAL := exec
.PHONY: exec tests

clean:
	rm -rf bin/*
