#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "raylib.h"
#include "wordList.h"
#include "theme.h"
#include "globals.h"
#include <string.h>
#include <stdbool.h>

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, GUESSING, LOSE, WIN, SETTINGS } GameScreen;

// Extendable to read from save and include winstreak, etc.
typedef struct GameState {
    Theme *theme;
    bool isHardMode;
    char greenLocked[NUM_LETTERS];    // '\0' = no lock, otherwise required letter at position
    char yellowRequired[NUM_LETTERS]; // Yellow letters that must appear in subsequent guesses
    int yellowCount;
    // Game window
    int screenHeight;
    int screenWidth;
    const char* windowTitle;

    // Guess cell sizes
    int cellSize;
    int cellOffsetY;
    int cellPadding;
    int cellFontSize;
    int cellBorderSize;

    // Keyboard parameters
    int keybPosY;
    int keybCellSize;
    int keybFontSize;
    int keybPadding;
    const char* deleteKey;
    const char* enterKey;

    // Notification parameters
    int shakeSkew;
    float shakeDuration;
    int notifPosY;
    int notifPadding;
    int notifFontSize;

    // Data
    const char* wordsPath;

    // End screen
    int restartOffsetY;
    int restartTextSize;
    int endTextSize;
    int endTextOffsetY;
    
    // Guessing
    WordList *wordList;
    const char* targetWord;
    int guessRowIdx;
    int guessLetterIdx;

    // Guessing Game State Params
    int guessingWordIdx;
    int numLettersCorrect;

    GameScreen gameScreen;
    int framesCounter;
} GameState;

GameState *MakeDefaultGameState();
void RestartGame(GameState *g);
void FreeGameState(GameState *g);

#endif // GAME_STATE_H