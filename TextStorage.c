#include "TextStorage.h"

// Initialize TextStorage object 
TextStorage* createTextStorage() {
	TextStorage* str = (TextStorage*)malloc(sizeof(TextStorage));
	str->size = 2;
	str->length = 1;
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
		str->strings = (DynamicString**)realloc(str->strings, str->size+1);
	}
	str->strings[str->length-1] = createDynamicString();	
}

// Add a char at the end of TextStorage
// If appending would make the length exceed size Then increase text size
void appendTextStorage(TextStorage* str, char c) {
	if(c == '\n') {
		addLine(str);
	} else{
		insertDynamicString(str->strings[str->length-1], c);
	}
}

// Delete character at the front of the Text Storage
void backSpaceTextStorage(TextStorage* str) {
	backSpaceDynamicString(str->strings[0]);
}

// Free all the allocated memory for TextStorage
void freeTextStorage(TextStorage* str) {
	freeDynamicString(str->strings[str->length-1]);
	free(str);
}

// Preform any preprocessing TextStorage needs
DynamicString* getTextStorageText(TextStorage* str) {
	DynamicString* total = createDynamicString();
	for(int i = 0; i < str->length; i++) {
		for(int j = 0; j < str->strings[i]->length; j++) {
			insertDynamicString(total, str->strings[i]->str[j]);
		}
		insertDynamicString(total, '\n');
	}
	return total;
}

