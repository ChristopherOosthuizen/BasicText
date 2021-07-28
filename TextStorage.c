#include "TextStorage.h"

TextStorage* createTextStorage() {
	TextStorage* str = (TextStorage*)malloc(sizeof(TextStorage));
	str->size = 2;
	str->length = 0;
	str->str = (char*)malloc(str->size+1);
}

void appendTextStorage(TextStorage* str, char c) {
	str->length++;
	if(str->size <= str->length) {
		str->size *= 2;
		str->str = (char*)realloc(str->str, str->size+1);
	}
	str->str[str->length-1] = c;
}

void backSpaceTextStorage(TextStorage* str) {
	str->length--;
	str->str[str->length] = '\0';
}

void freeTextStorage(TextStorage* str) {
	free(str->str);
	free(str);
}


