all: mod.so main

mod.so: mod.v
	v -cc gcc -g -shared -enable-globals -o mod .
	# v -prod -cc gcc -g -shared -enable-globals -o mod .

main: main.c
	gcc -o main main.c -ldl -lpthread

clean:
	rm -rf main *.so *.dSYM *.dylib
