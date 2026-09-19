all: 
	prepare && compile

prepare:
	rm -rf build
	mkdir build

compile: 
	cd build && cmake -S .. -B .
