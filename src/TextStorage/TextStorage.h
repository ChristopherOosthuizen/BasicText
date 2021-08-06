#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H 
#include "../DynamicString/DynamicString.h"


typedef struct {
	DynamicString** strings;
	size_t size;
	size_t length;
	int x;
	int y;
	int height;
	int bottom;
	int topSet;
	int tabSize;
} TextStorage;


extern TextStorage* createTextStorage();
extern void appendTextStorage(TextStorage* str, char c);
extern void backSpaceTextStorage(TextStorage* str);
extern void freeTextStorage(TextStorage* str);
extern DynamicString* getTextStorageText(TextStorage* str);
extern DynamicString* getTextStorageTextColor(TextStorage* str);
extern void setTopBottom(TextStorage* storage, int height, int bottom);
#endif // TextStorage
