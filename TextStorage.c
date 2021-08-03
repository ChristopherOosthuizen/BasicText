#include "TextStorage.h"
#include <ncurses.h>


// Initialize TextStorage object 
TextStorage* createTextStorage() {
	TextStorage* str = (TextStorage*)malloc(sizeof(TextStorage));
	str->size = 2;
	str->length = 1;
	str->x = 0;
	str->y = 0;
	str->top = 0;
	str->bottom = 0; 
	str->topSet = 0;
	str->strings = (DynamicString**)malloc(str->size+1);
	str->strings[0] = createDynamicString();
	return str;

}

// Set the top and bottom for displaying purposes
void setTopBottom(TextStorage* storage, int top, int bottom) {
		storage->top  = top;
		storage->bottom = bottom;
		storage->topSet = 1;
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

	DynamicString* newline = splitDynamicString(str->strings[str->y],str->x);
	str->strings[++str->y] = newline; 
}

void handleMouse(TextStorage* str) {
	MEVENT event;
	if(getmouse(&event) == OK) {
		if(event.bstate & BUTTON1_PRESSED) {
			str->x = event.x;
			str->y = str->top + event.y;
		}else if(event.bstate & BUTTON4_PRESSED) {
			appendTextStorage(str, 'a');
		}
	}

}

// Add chacter to the top of the text storage
// if the new character is a newline character
// expand string stack
void appendTextStorage(TextStorage* str, char c) {
	switch(c) {
		case -103: handleMouse(str);break;
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
	}else if(str->topSet && str->y > str->bottom) {
		str->top += str->y-str->bottom;
		str->bottom = str->y;
	}else if(str->topSet && str->y < str->top) {
		str->bottom -= str->top-str->y;
		str->top = str->y;
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
		addDynamicStrings(str->strings[str->y], str->strings[str->y+1]);
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
	for(int i = str->top; i < str->bottom; i++) {

		addDynamicStrings(total, str->strings[i]);	
		insertDynamicString(total, '\n', total->length);
	}
	backSpaceDynamicString(total,total->length);
	return total;
}

