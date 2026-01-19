#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include "inputProcessing.h"
#include "draw.h"
#include "guessing.h"
#include "globals.h"
#include "wordList.h"
#include "notification.h"
#include "settings.h"
#include "icon.h"
#include "gameState.h"
#include <stdio.h>

// ToDo: Consolidate into draw.c
static inline void ProcessNotifications(NotificationManager *nMgr, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int row, int frameCounter, GameState *g){
    if(DrawNotifications(nMgr, g) && nMgr->rowShake_s > 0){
        DrawRowShake(cells, row, frameCounter, g);
    }
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    GameState *gameState = MakeDefaultGameState();
    SetRandomSeed(1234); // ToDo: make this truly random

    WordList wordList = LoadWordList(gameState->wordsPath);
    const char *targetWord = GetRandomWord(&wordList);
    printf("DEBUG: Loaded %s\n", targetWord);
    InitWindow(gameState->screenWidth, gameState->screenHeight, gameState->windowTitle);
    // NOTE: Load resources (textures, fonts, audio) after Window initialization
    
    // Setup initial game state
    //GameScreen screen = TITLE;

    NotificationManager notificationManager;
    SetNotification(&notificationManager, NOTIFY_NONE);

    Icon *settingsIcon = MakeIcon(ICON_SETTINGS, (Rectangle){0, 0, 50, 50});

    int framesCounter = 0;

    LetterCell cells[NUM_GUESSES][NUM_LETTERS] = { 0 };

    int guessRowIdx = 0;
    int guessLetterIdx = 0;
    // Guessing state parameters
    int guessingWordIndex = 0;
    int numCorrect = 0;

    // Initialize letter cells
    for (int r = 0; r < NUM_GUESSES; r++){
        for (int c = 0; c < NUM_LETTERS; c++){
            Vector2 position = { .x = c, .y = r };
            InitLetterCellAt(&cells[r][c], position, gameState);
        }
    }

    // ToDo: Actually use cell params to make keyb
    Keyboard *keyb = CreateKeyboard(
        gameState->keybPosY, 
        (Vector2) {gameState->keybCellSize, gameState->keybCellSize}, 
        gameState->keybFontSize, 
        gameState->keybPadding, 
        LIGHTGRAY, 
        YELLOW
    );

    // Desired framerate
    SetTargetFPS(60);
    // ----------------------------------------------------------------

    // Main loop
    while(!WindowShouldClose()){
        // Update
        // ------------------------------------------------------------
        switch (gameState->gameScreen){
            case LOGO:
            {
                framesCounter++;
                // After 3 seconds, change to title screen
                if(framesCounter > 180){
                    gameState->gameScreen = TITLE;
                    framesCounter = 0;
                }
            } break;
            case TITLE:
            {
                framesCounter++;
                if (IsKeyPressed(KEY_ENTER)) gameState->gameScreen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
                framesCounter++;
                ProcessKeyboardInputs(&wordList, cells, guessRowIdx, &guessLetterIdx, &notificationManager, gameState);
                ProcessMouseInputs(&wordList, cells, keyb, guessRowIdx, &guessLetterIdx, &notificationManager, settingsIcon, gameState);
                UpdateNotification(&notificationManager, GetFrameTime());
            } break;
            case GUESSING:
            {
                framesCounter++;
                ProcessGuess(cells, targetWord, &guessRowIdx, &guessLetterIdx, &guessingWordIndex, &numCorrect, gameState);
                UpdateNotification(&notificationManager, GetFrameTime());
            } break;
            case WIN:
            case LOSE:
            {
                framesCounter++;
                UpdateNotification(&notificationManager, GetFrameTime());
                if(IsKeyPressed(KEY_ENTER)){
                    // Reset game
                    guessRowIdx = 0;
                    guessLetterIdx = 0;
                    guessingWordIndex = 0;
                    numCorrect = 0;
                    // Reset keyboard

                    // Reset cells
                    for (int r = 0; r < NUM_GUESSES; r++){
                        for (int c = 0; c < NUM_LETTERS; c++){
                            cells[r][c].state = NO_GUESS;
                            cells[r][c].letter[0] = '\0';
                        }
                    }
                    
                    targetWord = GetRandomWord(&wordList);

                    gameState->gameScreen = GAMEPLAY;
                }
            } break;
            case SETTINGS:
            {
                // ToDo: Settings screen input processor
            } break;
            default: break;
        }
        // ------------------------------------------------------------


        // Draw
        // ------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(gameState->gameScreen){
                case LOGO:
                {
                    DrawText("LOGO SCREEN", 20, 20, 20, DARKBLUE);
                    DrawText("WAIT for 3 seconds...", 290, 220, 20, GRAY);
                } break;
                case TITLE:
                {
                    DrawRectangle(0, 0, gameState->screenWidth, gameState->screenHeight, DARKBROWN);
                    DrawText("\"WORDLE\"", (GetScreenWidth() - MeasureText("\"WORDLE\"", 40))/2, GetScreenHeight()/2, 40, DARKGREEN);
                    // Every half second toggle text (60 fps)
                    if ((framesCounter/30)%2 == 0)
                        DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
                } break;
                case GUESSING:
                case GAMEPLAY:
                {
                    DrawMainGameplayScreen(cells, keyb, gameState->screenWidth, gameState->screenHeight);
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter, gameState);
                } break;
                case WIN:
                {
                    DrawMainGameplayScreen(cells, keyb, gameState->screenWidth, gameState->screenHeight);
                    
                    DrawText("WELL DONE!", (GetScreenWidth() - MeasureText("WELL DONE!", gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, DARKGREEN);
                    if((framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter, gameState);
                } break;
                case LOSE:
                {
                    DrawMainGameplayScreen(cells, keyb, gameState->screenWidth, gameState->screenHeight);
                    const char* endMessage = TextFormat("SO CLOSE! IT WAS %s.", targetWord);
                    DrawText(endMessage, (GetScreenWidth() - MeasureText(endMessage, gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, DARKPURPLE);
                    if((framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter, gameState);
                } break;
                case SETTINGS:
                {
                    DrawMainGameplayScreen(cells, keyb, gameState->screenWidth, gameState->screenHeight);
                    DrawSettingsScreen();
                }
                default: break;
            }
            settingsIcon->draw(settingsIcon);
        EndDrawing();
        // ------------------------------------------------------------
    }

    // De-Initialize
    // ----------------------------------------------------------------

    CloseWindow();
    ReleaseKeyboard(keyb);
    FreeWordList(&wordList);
    FreeIcon(settingsIcon);
    FreeGameState(gameState);
    // ----------------------------------------------------------------
    return 0;
}