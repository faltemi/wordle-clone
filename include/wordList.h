#ifndef WORDLIST_H
#define WORDLIST_H

#include <stdlib.h>
#include <string.h>
#include "raylib.h"

typedef struct WordList {
    char *fileBuffer;      // The raw file data
    const char **words;    // Array of pointers to strings
    int wordCount;
} WordList;

WordList LoadWordList(const char *fileName);
const char* GetRandomWord(WordList *list);
bool IsValidWord(WordList *list, const char *guess);
void FreeWordList(WordList *list);

#endif // WORDLIST_H