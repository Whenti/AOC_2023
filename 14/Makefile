build_and_run: build run

build: solve.out

solve.out: solve.cpp $(wildcard *.h)
	clang++-17 -w -std=c++23 -o solve.out solve.cpp

run:
	./solve.out < input
