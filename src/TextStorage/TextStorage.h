#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H 
#include "../DynamicString/DynamicString.h"


typedef struct {
	DynamicString** strings;
	size_t size;
	size_t length;
	int x;
	int y;
	int top;
	int bottom;
	int topSet;
} TextStorage;


extern TextStorage* createTextStorage();
extern void appendTextStorage(TextStorage* str, char c);
extern void backSpaceTextStorage(TextStorage* str);
extern void freeTextStorage(TextStorage* str);
extern DynamicString* getTextStorageText(TextStorage* str);
extern void setTopBottom(TextStorage* storage, int top, int bottom);
#endif // TextStorage
