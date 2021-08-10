#include <unistd.h>
#include <ncurses.h>
#include "TextStorage/TextStorage.h"
#include <stdio.h>
#include <sys/ioctl.h>

void readFileContent(char* file_name, TextStorage* storage) {
		FILE* file;
		file = fopen(file_name, "r");
		fseek(file, 0L, SEEK_END);
		int file_size = ftell(file);
		fseek(file, 0L, SEEK_SET);
		char file_content[file_size];
		fread(file_content, 1, file_size, file);
		for(int i = 0; i < file_size; i++) {
			appendTextStorage(storage,file_content[i]);
		}
		fclose(file);
}

void writeToFile(char* file_name, TextStorage* storage) {
	FILE* file;
	file = fopen(file_name, "w+");
	int height = storage->height;
	int bottom = storage->bottom;
	setTopBottom(storage,storage->length, storage->length, -1);
	DynamicString* content = getTextStorageText(storage); 
	setTopBottom(storage,height, bottom, -1);

	fprintf(file, content->str); 
	freeDynamicString(content);
	fclose(file);
}

void displayTextStorage(TextStorage* storage, int blink) {
	clear();

	//attron(COLOR_PAIR(1));
	int top = storage->bottom-storage->height;


	for(int i = top; i< storage->length && i< storage->bottom+1; i++) {
			printw("%5d| ", i);
			if(i == storage->y) {
				DynamicString* str = createDynamicString();
				addDynamicStrings(str, storage->strings[i]);
				if(blink) {
					insertDynamicString(str,'|', storage->x);
				} else{
					insertDynamicString(str,' ', storage->x);

				}
				addstr(str->str);
				freeDynamicString(str);
			}else {
				addstr(storage->strings[i]->str);
			}
			addstr("\n");
	}
	//attroff(COLOR_PAIR(1));

	refresh();

}

void setHeight(TextStorage* str) {
	struct winsize window_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
	int height = window_size.ws_row; 
        int width = window_size.ws_col;
		setTopBottom(str,height-1, str->bottom, width);

	
}

int main(int argc, char* argv[]) {
	TextStorage* str = createTextStorage();
	if(argc > 1 && access(argv[1], F_OK) == 0) {
		readFileContent(argv[1], str);
	} 
	initscr();
	raw();
	noecho();
	clear();
	cbreak();
	keypad(stdscr, true);
	mouseinterval(0);
	curs_set(0);
	timeout(300);
	mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED | BUTTON3_PRESSED |
		REPORT_MOUSE_POSITION, NULL);
	struct winsize window_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
	int height = window_size.ws_row; 
	int width = window_size.ws_col;
	int bottom;
	if(height < str->y) {
		bottom = str->y;
	} else {
		bottom = height-1;
	}

	setTopBottom(str, height-1, bottom, width);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	int blink = 0;
	displayTextStorage(str,blink);
	while(TRUE) {
		blink = !blink;
		char c = getch();
		if(c == 17) {
			break;
		} else if(c == 19) {
			writeToFile(argv[1], str);	
		} else {
			appendTextStorage(str,c); 
		}
		displayTextStorage(str,blink);
		setHeight(str);

		}
	endwin();
	freeTextStorage(str);
	return EXIT_SUCCESS;
}
