#include "DynamicString.h"

DynamicString* createDynamicString() {
	DynamicString* str = (DynamicString*)malloc(sizeof(DynamicString));
	str->size = 2;
	str->length = 0;
	str->str = (char*)malloc(str->size+1);
	str->str[0] = '\0';
	return str;
}

// Add a char at the end of DynamicString
// If appending would make the length exceed size Then increase text size
void insertDynamicString(DynamicString* str, char c, int index) {
	str->length++;
	if(str->size <= str->length) {
		str->size *= 2;
		str->str = (char*)realloc(str->str, str->size+1);
	}
	if(index >= str->length-1) {
		str->str[str->length-1] = c;
		str->str[str->length] = '\0';
		return;
	}
	for(int i = str->length-1; i >= index; i--) {
		str->str[i] = str->str[i-1];
	}
  str->str[index] = c;
  str->str[str->length] = '\0';
}

// Add two Dynamic strings by modifiying str1 but leaving str2 unchanged
void addDynamicStrings(DynamicString* str1, DynamicString* str2) {
	for(int i = 0; i < str2->length; i++) {
		insertDynamicString(str1,str2->str[i], str1->length);
	}
}

// Split a dynamic string into two parts modifing the input and retruning
// a new dynamic string holding the rest of the content
DynamicString* splitDynamicString(DynamicString* str, int index) {
	DynamicString* newline = createDynamicString();
	for(int i = index; i < str->length; i++) {
		insertDynamicString(newline, str->str[i], i);	
	}
	str->str[index] = '\0'; 
	str->length -= str->length-index;
	return newline;
		
}

// Delete character at the front of the DynamicString 
void backSpaceDynamicString(DynamicString* str, int index) {
	if(str->length > 0) {
		for(int i = index; i < str->length-1; i++) {
			str->str[i] = str->str[i+1];
		}
		str->length--;
		str->str[str->length] = '\0';
	}
}

// Free all the allocated memory for DynamicString 
void freeDynamicString(DynamicString* str) {
	free(str->str);
	free(str);
}

