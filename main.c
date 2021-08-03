#include <unistd.h>
#include <ncurses.h>
#include "TextStorage.h"
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
	int top = storage->top;
	int bottom = storage->bottom;
	
	setTopBottom(storage,0, storage->length);
	DynamicString* content = getTextStorageText(storage); 
	setTopBottom(storage,top, bottom);

	fprintf(file, content->str); 
	freeDynamicString(content);
	fclose(file);
}

void displayTextStorage(TextStorage* storage) {
	clear();
	DynamicString* display_str = getTextStorageText(storage);
	addstr(display_str->str);
	freeDynamicString(display_str);
	refresh();
	move(storage->y -storage->top, storage->x);
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
	mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED | BUTTON3_PRESSED | 
		REPORT_MOUSE_POSITION, NULL);
	struct winsize window_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
	int height = window_size.ws_row; 
	int width = window_size.ws_col;
	int bottom;
	int top;
	if(height < str->y) {
		bottom = str->y;
		top = str->length-height;
	} else {
		bottom = height-1;
		top = 0;
	}
	
	setTopBottom(str, top, bottom);
	displayTextStorage(str);
	while(TRUE) {
		char c = getch();
		if(c == 17) {
			break;
		} else if(c == 19) {
			writeToFile(argv[1], str);	
		} else {
			appendTextStorage(str,c); 
		}
		displayTextStorage(str);

		}
	endwin();
	freeTextStorage(str);
	printf("success");
	return EXIT_SUCCESS;
}
