#include "TextStorage.h"

// Initialize TextStorage object 
TextStorage* createTextStorage() {
	TextStorage* str = (TextStorage*)malloc(sizeof(TextStorage));
	str->size = 2;
	str->length = 0;
	str->str = (char*)malloc(str->size+1);
}

// Add a char at the end of TextStorage
// If appending would make the length exceed size Then increase text size
void appendTextStorage(TextStorage* str, char c) {
	str->length++;
	if(str->size <= str->length) {
		str->size *= 2;
		str->str = (char*)realloc(str->str, str->size+1);
	}
	str->str[str->length-1] = c;
}

// Delete character at the front of the Text Storage
void backSpaceTextStorage(TextStorage* str) {
	if(str->length > 0) {
		str->length--;
		str->str[str->length] = '\0';
	}
}

// Free all the allocated memory for TextStorage
void freeTextStorage(TextStorage* str) {
	free(str->str);
	free(str);
}

// Preform any preprocessing TextStorage needs
char* getTextStorageText(TextStorage* str) {
	return str->str;
}

