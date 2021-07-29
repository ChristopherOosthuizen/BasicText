#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H 
#include "DynamicString.h"


typedef struct {
	DynamicString** strings;
	size_t size;
	size_t length;
	int x;
	int y;
} TextStorage;


extern TextStorage* createTextStorage();
extern void appendTextStorage(TextStorage* str, char c);
extern void backSpaceTextStorage(TextStorage* str);
extern void freeTextStorage(TextStorage* str);
extern DynamicString* getTextStorageText(TextStorage* str);
#endif // TextStorage
