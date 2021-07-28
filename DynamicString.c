#include "DynamicString.h"

DynamicString* createDynamicString() {
	DynamicString* str = (DynamicString*)malloc(sizeof(DynamicString));
	str->size = 2;
	str->length = 0;
	str->str = (char*)malloc(str->size+1);
	return str;
}

// Add a char at the end of TextStorage
// If appending would make the length exceed size Then increase text size
void insertDynamicString(DynamicString* str, char c) {
	str->length++;
	if(str->size <= str->length) {
		str->size *= 2;
		str->str = (char*)realloc(str->str, str->size+1);
	}
	str->str[str->length-1] = c;
	str->str[str->length] = '\0';
}

// Delete character at the front of the Text Storage
void backSpaceDynamicString(DynamicString* str) {
	if(str->length > 0) {
		str->length--;
		str->str[str->length] = '\0';
	}
}

// Free all the allocated memory for TextStorage
void freeDynamicString(DynamicString* str) {
	free(str->str);
	free(str);
}

