#include "TextStorage.h"
#include <ncurses.h>


// Initialize TextStorage object 
TextStorage* createTextStorage() {
	TextStorage* str = (TextStorage*)malloc(sizeof(TextStorage));
	str->size = 2;
	str->length = 1;
	str->x = 0;
	str->y = 0;
	str->strings = (DynamicString**)malloc(str->size+1);
	str->strings[0] = createDynamicString();
	return str;

}

// Create a new line at the end of the Text storage and if length excedes 
// size then increase size
void addLine(TextStorage* str) {
	str->length++;
	if(str->length >= str->size) {
		str->size *= 2;
		str->strings = (DynamicString**)realloc(str->strings, sizeof(DynamicString*)*(str->size+1));
	}
	for(int i = str->length; i > str->y; i--) {
		str->strings[i] = str->strings[i-1];
	}

	DynamicString* newline = createDynamicString();
	for(int i = str->x; i < str->strings[str->y]->length; i++) {
		insertDynamicString(newline, str->strings[str->y]->str[i], i);	
	}
	str->strings[str->y]->str[str->x] = '\0'; 
	str->strings[str->y]->length -= str->strings[str->y]->length-str->x;
	str->y++;
	str->strings[str->y] = newline; 


}

// Add chacter to the top of the text storage
// if the new character is a newline character
// expand string stack
void appendTextStorage(TextStorage* str, char c) {
	switch(c) {
		case -103: {
											MEVENT event;
											if(getmouse(&event) == OK) {
												str->x = event.x;
												str->y = event.y;
											}
											break;
										}
		case 18: backSpaceTextStorage(str);break;
		case 2: str->y++; break; // DOWN
		case 3: str->y--; break; // UP
		case 4: str->x--; break; // LEFT
		case 5: str->x++; break; // RIGHT
		case 127: backSpaceTextStorage(str); break; // Delete key
		case '\n': {
									addLine(str);
									str->x = 0;
									break;
							 }
		default: {
							insertDynamicString(str->strings[str->y],  c,str->x );
							str->x++; break;
						 }
	}
	if(str->y < 0) {
		str->y = 0;
	}
	if(str->length <= str->y) {
		str->y = str->length-1;
	}

	if(str->x < 0) {
		str->x = 0;	
	}
	if(str->x >= str->strings[str->y]->length) {
		str->x = str->strings[str->y]->length;
	}

}

// Delete character at the front of the Text Storage
// If ther is not text on the line and at the top of file do nothing
void backSpaceTextStorage(TextStorage* str) {
	if(str->y > 0 && str->x < 1){
		str->length--;
		str->y--;
		str->x = str->strings[str->y]->length;
		for(int i = 0; i < str->strings[str->y+1]->length; i++) {
			insertDynamicString(str->strings[str->y], str->strings[str->y+1]->str[i],str->strings[str->y]->length);
		}
		freeDynamicString(str->strings[str->y+1]);
	} else {
		str->x--;
		backSpaceDynamicString(str->strings[str->y], str->x);
	}

}

// Free all the allocated memory for TextStorage
void freeTextStorage(TextStorage* str) {
	freeDynamicString(str->strings[str->length-1]);
	free(str);
}

// Create the string reprecentation of text storage
// Intended to be used as the text showed to the user
DynamicString* getTextStorageText(TextStorage* str) {
	DynamicString* total = createDynamicString();
	int x = 0;
	for(int i = 0; i < str->length; i++) {
		for(int j = 0; j < str->strings[i]->length; j++) {
			insertDynamicString(total, str->strings[i]->str[j], x);
			x++;
		}
		insertDynamicString(total, '\n',x);
		x++;
	}
	backSpaceDynamicString(total,total->length);
	return total;
}

