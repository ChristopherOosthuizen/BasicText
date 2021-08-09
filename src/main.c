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
	
	setTopBottom(storage,storage->length, storage->length);
	DynamicString* content = getTextStorageText(storage); 
	setTopBottom(storage,height, bottom);

	fprintf(file, content->str); 
	freeDynamicString(content);
	fclose(file);
}

void displayTextStorage(TextStorage* storage) {
	clear();

	//attron(COLOR_PAIR(1));
	int top = storage->bottom-storage->height;

	for(int i = top; i< storage->length && i< storage->bottom+1; i++) {
			printw("%5d| ", i);
			addstr(storage->strings[i]->str);
			addstr("\n");
	}
	//attroff(COLOR_PAIR(1));

	refresh();
	move(storage->y -top, storage->x+7);

}

void setHeight(TextStorage* str) {
	struct winsize window_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
	int height = window_size.ws_row; 
		setTopBottom(str,height-1, str->bottom);

	
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
	if(height < str->y) {
		bottom = str->y;
	} else {
		bottom = height-1;
	}

	setTopBottom(str, height-1, bottom);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);

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
		setHeight(str);

		}
	endwin();
	freeTextStorage(str);
	printf("success");
	return EXIT_SUCCESS;
}
