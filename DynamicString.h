#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H
#include <stdlib.h>

typedef struct {
	char* str;
	size_t size;
	size_t length;
} DynamicString;

// Initialize DynamicString and all its values 
// ex: DynamicString* str = createDynamicString();
extern DynamicString* createDynamicString(); 
// Insert a character at the front of the dynamic string
// ex: insertDynamicString(str, 'c'); c is now at the top of the string
extern void insertDynamicString(DynamicString* str, char c);
// Delete the character at the front the dynamic string
extern void backSpaceDynamicString(DynamicString* str);
// Free dynamic string
extern void freeDynamicString(DynamicString* str);
#endif // DynamicString
