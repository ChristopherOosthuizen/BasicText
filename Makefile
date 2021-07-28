make:
	gcc -g main.c DynamicString.h DynamicString.c TextStorage.h TextStorage.c -std=c99 -lncurses
	./a.out

