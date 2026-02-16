#include "gameState.h"
#include <stdlib.h>

GameState *MakeDefaultGameState(){
    GameState *g = malloc(sizeof(GameState));
    g->theme = MakeTheme();
    g->screenHeight = 600;
    g->screenWidth = 800;
    g->windowTitle = "Wordle Clone";

    g->cellSize = 50;
    g->cellOffsetY = 70;
    g->cellPadding = 5;
    g->cellFontSize = 20;
    g->cellBorderSize = 2;

    g->keybPosY = 430;
    g->keybCellSize = 40;
    g->keybFontSize = 20;
    g->keybPadding = 10;
    g->deleteKey = "<";
    g->enterKey = "#";

    g->shakeSkew = 5;
    g->shakeDuration = 1.0f;
    g->notifPosY = 20;
    g->notifPadding = 20;
    g->notifFontSize = 20;

    g->wordsPath = "data/words.txt";
    g->wordList = LoadWordList(g->wordsPath);
    g->targetWord = GetRandomWord(g->wordList);

    g->restartOffsetY = 100;
    g->restartTextSize = 20;

    g->endTextSize = 40;
    g->endTextOffsetY = 10;

    g->guessRowIdx = 0;
    g->guessLetterIdx = 0;
    g->guessingWordIdx = 0;
    g->numLettersCorrect = 0;
    
    g->gameScreen = TITLE;
    g->framesCounter = 0;

    g->settings = MakeDefaultSettingsState();
    return g;
}

void RestartGame(GameState *g){
    g->guessRowIdx = 0;
    g->guessLetterIdx = 0;
    g->guessingWordIdx = 0;
    g->numLettersCorrect = 0;
    g->gameScreen = GAMEPLAY;
    g->targetWord = GetRandomWord(g->wordList);
}

void FreeGameState(GameState *g){
    FreeWordList(g->wordList);
    FreeSettingsState(g->settings);
    FreeTheme(g->theme);
    free(g);
}