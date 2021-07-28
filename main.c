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
	int x = 0;
	int y = 0;
	while(TRUE) {
		char c = getch();
		switch(c) {
			case 2: {
								y++;
								move(y+1,x); break; // DOWN
							}
			case 3: {
								y--;
								move(y-1, x); break; // UP
							}
			case 4: {
								x--;
								move(y, x-1); break; // LEFT
							}
			case 5: {
								x++;
								move(y, x+1); break; // RIGHT
							}
			case 127: backSpaceTextStorage(str); break; // Delete key
			default: {
								x++;
								appendTextStorage(str, c); break;
							 }
		}
		if(c > 5) {
			clear();
			DynamicString* display_str = getTextStorageText(str);
			addstr(display_str->str);
			freeDynamicString(display_str);
		}
		refresh();
	}
	endwin();
	freeTextStorage(str);
	return EXIT_SUCCESS;
}
