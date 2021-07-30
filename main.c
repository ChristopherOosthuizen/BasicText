#include <unistd.h>
#include <ncurses.h>
#include "TextStorage.h"
#include <stdio.h>

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
	DynamicString* content = getTextStorageText(storage); 
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
	move(storage->y, storage->x);
}

int main(int argc, char* argv[]) {
	TextStorage* str = createTextStorage();
	if(argc > 1) {
		readFileContent(argv[1], str);
	}
	initscr();
	raw();
	noecho();
	clear();
	cbreak();
	keypad(stdscr, true);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	displayTextStorage(str);
	while(TRUE) {
		char c = getch();
		endwin(); 

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
