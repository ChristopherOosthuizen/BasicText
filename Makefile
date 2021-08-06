make:
	gcc -g -Wall src/main.c src/DynamicString/DynamicString.h src/DynamicString/DynamicString.c src/TextStorage/TextStorage.h src/TextStorage/TextStorage.c -std=c99 -lncurses

install:
	make
	cp ./a.out /usr/bin/cedit
