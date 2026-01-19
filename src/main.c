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
#include <stdio.h>

// ToDo: Consolidate into draw.c
static inline void ProcessNotifications(NotificationManager *nMgr, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int row, int frameCounter){
    if(DrawNotifications(nMgr) && nMgr->rowShake_s > 0){
        DrawRowShake(cells, row, frameCounter);
    }
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    SetRandomSeed(1234); // ToDo: make this truly random

    WordList wordList = LoadWordList(WORDSPATH);
    const char *targetWord = GetRandomWord(&wordList);
    printf("DEBUG: Loaded %s\n", targetWord);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    // NOTE: Load resources (textures, fonts, audio) after Window initialization
    
    // Setup initial game state
    GameScreen screen = TITLE;

    NotificationManager notificationManager;
    SetNotification(&notificationManager, NOTIFY_NONE);

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
            InitLetterCellAt(&cells[r][c], position);
        }
    }

    // ToDo: Actually use cell params to make keyb
    Keyboard *keyb = CreateKeyboard(KEYB_POS_Y, (Vector2) {KEYB_CELL_SIZE, KEYB_CELL_SIZE}, LETTER_SIZE, 10, LIGHTGRAY, YELLOW);

    // Desired framerate
    SetTargetFPS(60);
    // ----------------------------------------------------------------

    // Main loop
    while(!WindowShouldClose()){
        // Update
        // ------------------------------------------------------------
        switch (screen){
            case LOGO:
            {
                framesCounter++;
                // After 3 seconds, change to title screen
                if(framesCounter > 180){
                    screen = TITLE;
                    framesCounter = 0;
                }
            } break;
            case TITLE:
            {
                framesCounter++;
                if (IsKeyPressed(KEY_ENTER)) screen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
                framesCounter++;
                ProcessKeyboardInputs(&wordList, cells, &screen, guessRowIdx, &guessLetterIdx, &notificationManager);
                ProcessMouseInputs(&wordList, cells, keyb, &screen, guessRowIdx, &guessLetterIdx, &notificationManager);
                UpdateNotification(&notificationManager, GetFrameTime());
            } break;
            case GUESSING:
            {
                framesCounter++;
                ProcessGuess(cells, &screen, targetWord, &guessRowIdx, &guessLetterIdx, &guessingWordIndex, &numCorrect);
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

                    screen = GAMEPLAY;
                }
            } break;
            default: break;
        }
        // ------------------------------------------------------------


        // Draw
        // ------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(screen){
                case LOGO:
                {
                    DrawText("LOGO SCREEN", 20, 20, 20, DARKBLUE);
                    DrawText("WAIT for 3 seconds...", 290, 220, 20, GRAY);
                } break;
                case TITLE:
                {
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBROWN);
                    DrawText("\"WORDLE\"", (GetScreenWidth() - MeasureText("\"WORDLE\"", 40))/2, GetScreenHeight()/2, 40, DARKGREEN);
                    // Every half second toggle text (60 fps)
                    if ((framesCounter/30)%2 == 0)
                        DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
                } break;
                case GUESSING:
                case GAMEPLAY:
                {
                    DrawMainGameplayScreen(cells, keyb, SCREEN_WIDTH, SCREEN_HEIGHT);
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter);
                } break;
                case WIN:
                {
                    DrawMainGameplayScreen(cells, keyb, SCREEN_WIDTH, SCREEN_HEIGHT);
                    
                    DrawText("WELL DONE!", (GetScreenWidth() - MeasureText("WELL DONE!", END_TEXT_SIZE))/2, END_TEXT_Y_OFFSET, END_TEXT_SIZE, DARKGREEN);
                    if((framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + RESTART_Y_OFFSET, RESTART_TEXT_SIZE, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter);
                } break;
                case LOSE:
                {
                    DrawMainGameplayScreen(cells, keyb, SCREEN_WIDTH, SCREEN_HEIGHT);
                    const char* endMessage = TextFormat("SO CLOSE! IT WAS %s.", targetWord);
                    DrawText(endMessage, (GetScreenWidth() - MeasureText(endMessage, END_TEXT_SIZE))/2, END_TEXT_Y_OFFSET, END_TEXT_SIZE, DARKPURPLE);
                    if((framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + RESTART_Y_OFFSET, RESTART_TEXT_SIZE, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, cells, guessRowIdx, framesCounter);
                } break;
                default: break;
            }
            DrawSettings();
        EndDrawing();
        // ------------------------------------------------------------
    }

    // De-Initialize
    // ----------------------------------------------------------------

    CloseWindow();
    ReleaseKeyboard(keyb);
    FreeWordList(&wordList);
    // ----------------------------------------------------------------
    return 0;
}