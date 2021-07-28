#include <unistd.h>
#include <ncurses.h>
#include "TextStorage.h"

int main() {
	TextStorage* str = createTextStorage();
	initscr();
	noecho();
	while(TRUE) {
		char c = getch();
		switch(c) {
			case 127: backSpaceTextStorage(str); break;
			default: appendTextStorage(str, c); break;
		}
		clear();
		addstr(getTextStorageText(str));
		refresh();
	}
	endwin();
	freeTextStorage(str);
	return EXIT_SUCCESS;
}
