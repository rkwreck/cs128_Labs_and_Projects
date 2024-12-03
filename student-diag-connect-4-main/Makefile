CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -O0 -gdwarf-4 


exec: bin/exec

bin/exec: ./src/main.cc ./src/functions.cc ./includes/functions.hpp
	$(CXX) $(CXX_FLAGS) ./src/main.cc ./src/functions.cc  -o $@


.DEFAULT_GOAL := exec
.PHONY: exec

clean:
	rm -rf bin/*
