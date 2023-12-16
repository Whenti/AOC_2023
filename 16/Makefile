build_and_run: build i

build: solve.out

solve.out: solve.cpp $(wildcard *.h)
	clang++-17 -w -std=c++23 -o solve.out solve.cpp

e:
	./solve.out < example
i:
	./solve.out < input
