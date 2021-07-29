#include <unistd.h>
#include <ncurses.h>
#include "TextStorage.h"
#include <stdio.h>

int main() {
	TextStorage* str = createTextStorage();
	initscr();
	noecho();
	clear();
	cbreak();
	keypad(stdscr, true);
	refresh();
	timeout(30000);
	while(TRUE) {
		char c = getch();
		appendTextStorage(str,c); 
		clear();
		DynamicString* display_str = getTextStorageText(str);
		addstr(display_str->str);
		freeDynamicString(display_str);
		refresh();
		move(str->y, str->x);
	}
	endwin();
	freeTextStorage(str);
	return EXIT_SUCCESS;
}
