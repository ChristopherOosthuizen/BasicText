#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H 
#include <stdlib.h>


typedef struct {
	char* str;
	size_t size;
	size_t length;
} TextStorage;


extern TextStorage* createTextStorage();
extern void appendTextStorage(TextStorage* str, char c);
extern void backSpaceTextStorage(TextStorage* str);
extern void freeTextStorage(TextStorage* str);
extern char* getTextStorageText(TextStorage* str);
#endif // TextStorage
