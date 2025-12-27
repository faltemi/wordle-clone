#include "wordList.h"

WordList LoadWordList(const char *fileName){
    WordList list = {0};
    
    list.fileBuffer = LoadFileText(fileName);
    if (!list.fileBuffer) return list;

    int count = 0;
    for (int i = 0; list.fileBuffer[i]; i++) {
        if (list.fileBuffer[i] == '\n') count++;
    }
    list.words = (const char **)malloc(sizeof(char*) * count);
    list.wordCount = count;

    int wordIdx = 0;
    char *cursor = list.fileBuffer;
    list.words[wordIdx++] = cursor;

    for (int i = 0; list.fileBuffer[i]; i++) {
        if (list.fileBuffer[i] == '\n') {
            list.fileBuffer[i] = '\0'; // Terminate current word
            
            // If there is more text, point to the next word
            if (list.fileBuffer[i+1] != '\0') {
                list.words[wordIdx++] = &list.fileBuffer[i+1];
            }
        }
        // Handle Windows \r\n line endings
        if (list.fileBuffer[i] == '\r') list.fileBuffer[i] = '\0';
    }

    return list;
}

const char* GetRandomWord(WordList *list) {
    if (list->wordCount == 0) return "ERROR";
    int index = GetRandomValue(0, list->wordCount - 1);
    return list->words[index];
}

// Comparator for bsearch
int CompareWords(const void *a, const void *b) {
    const char *key = (const char *)a;
    const char * const *entry = (const char * const *)b;
    return strcmp(key, *entry);
}

bool IsValidWord(WordList *list, const char *guess) {
    // bsearch returns a pointer to the found item, or NULL
    void *found = bsearch(guess, list->words, list->wordCount, sizeof(char*), CompareWords);
    return (found != NULL);
}

void FreeWordList(WordList *list) {
    if (list->words) free(list->words);
    if (list->fileBuffer) UnloadFileText(list->fileBuffer);
    list->wordCount = 0;
}
