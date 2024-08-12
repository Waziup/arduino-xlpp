#!make

.PHONY: test-simple test-full

clean:
	rm -rf build

test-simple:
	mkdir -p build
	g++ src/xlpp.cpp test/simple/main.cpp -o build/test-simple
	./build/test-simple

test-full:
	mkdir -p build
	g++ src/xlpp.cpp test/full/main.cpp -o build/test-full
	./build/test-full