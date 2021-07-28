#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H
#include <stdlib.h>

typedef struct {
	char* str;
	size_t size;
	size_t length;
} DynamicString;


extern DynamicString* createDynamicString();
extern void insertDynamicString(DynamicString* str, char c);
extern void backSpaceDynamicString(DynamicString* str);
extern void freeDynamicString(DynamicString* str);
#endif // DynamicString
