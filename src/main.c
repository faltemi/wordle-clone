#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include <stdio.h>

#define NUM_GUESSES         6
#define NUM_LETTERS         5
#define CELL_SIZE           50
#define CELL_Y_OFFSET       50
#define CELL_PADDING        5
#define LETTER_SIZE         20
#define DELETE "<"
#define ENTER "#"

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, GUESSING, ENDING } GameScreen;

// Position calculation for letter cells
static inline void InitLetterCellAt(LetterCell *cell, Vector2 position) {
    // Center with respect to padding (which isnt ba)
    const int paddingX = position.x == 0 ? 0 : CELL_PADDING;
    const int paddingY = position.y == 0 ? 0 : CELL_PADDING;

    const int totalW = NUM_LETTERS*CELL_SIZE + CELL_PADDING*(NUM_LETTERS-1);
    const int offsetX = (GetScreenWidth() - totalW)/2;

    const int posX = position.x*(CELL_SIZE + paddingX) + offsetX;
    const int posY = position.y*(CELL_SIZE + paddingY) + CELL_Y_OFFSET;

    InitLetterCell(cell, (Vector2){posX, posY}, (Vector2){CELL_SIZE, CELL_SIZE}, LETTER_SIZE);
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    // Window setup parameters
    const int screenWidth = 800;
    const int screenHeight = 600;
    const char *windowTitle = "Wordle Clone";

    const char *testWord = "AMUSE";

    InitWindow(screenWidth, screenHeight, windowTitle);
    // NOTE: Load resources (textures, fonts, audio) after Window initialization
    
    // Setup initial game state
    GameScreen screen = TITLE;

    int framesCounter = 0;
    int gameResult = -1;

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
    Keyboard *keyb = createKeyboard((Vector2) {200,400}, (Vector2) {40, 40}, 20, 10, LIGHTGRAY, YELLOW);

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
                // ToDo: Gameplay logic
                if (IsKeyPressed(KEY_ENTER)) screen = ENDING;

                // Check for clicked keyboard key
                for(int i = 0; i < NUM_ROWS; ++i){
                    int num_keys = NUM_ROW_KEYS + (i == 0 ? 1 : 0);
                    for(int j = 0; j < num_keys; ++j){
                        if(CheckCollisionPointRec(GetMousePosition(),keyb->keys[i][j]->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                            // Key press logic: letter, enter, del
                            if(strcmp(keyb->keys[i][j]->letter, ENTER) == 0){
                                if(guessLetterIdx == NUM_LETTERS){
                                    // Change state to 'guessing', freeze input and guess each letter until done
                                    screen = GUESSING;
                                }
                                else{
                                    // Shake row and display 'not enough letters'
                                }
                            }
                            else if(strcmp(keyb->keys[i][j]->letter, DELETE) == 0){
                                if(guessLetterIdx != 0) guessLetterIdx--;
                                cells[guessRowIdx][guessLetterIdx].letter[0] = '\0';
                                cells[guessRowIdx][guessLetterIdx].state = NO_GUESS;
                            }
                            else{
                                if(guessLetterIdx < NUM_LETTERS){
                                    TextCopy(cells[guessRowIdx][guessLetterIdx].letter, keyb->keys[i][j]->letter);
                                    cells[guessRowIdx][guessLetterIdx].state = BEING_GUESSED;
                                    guessLetterIdx++;
                                }
                            }
                        }
                    }
                }
            } break;
            case GUESSING:
            {
                if(guessingWordIndex < NUM_LETTERS){
                    // Same letter
                    if(cells[guessRowIdx][guessingWordIndex].letter[0] == testWord[guessingWordIndex]){
                        cells[guessRowIdx][guessingWordIndex].state = CORRECT;
                        numCorrect++;
                    }
                    else{
                        bool letterInWord = false;
                        for(int i = guessingWordIndex; i < NUM_LETTERS; ++i){
                            if(cells[guessRowIdx][guessingWordIndex].letter[0] == testWord[i]){
                                letterInWord = true;
                                break;
                            }
                        }
                        cells[guessRowIdx][guessingWordIndex].state = letterInWord ? WRONG_POS : INCORRECT;
                    }
                    guessingWordIndex++;
                }
                else{
                    if(numCorrect == NUM_LETTERS){
                        // ToDo: Win state/win screen
                    }
                    guessingWordIndex = 0;
                    numCorrect = 0;
                    guessRowIdx++;
                    guessLetterIdx = 0;
                    screen = GAMEPLAY;
                }
            } break;
            case ENDING:
                {
                    framesCounter++;
                    // Game end logic
                    if (IsKeyPressed(KEY_ENTER)) screen = TITLE;
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
                    DrawRectangle(0, 0, screenWidth, screenHeight, DARKBROWN);
                    DrawText("\"WORDLE\"", (GetScreenWidth() - MeasureText("\"WORDLE\"", 40))/2, GetScreenHeight()/2, 40, DARKGREEN);
                    // Every half second toggle text (60 fps)
                    if ((framesCounter/30)%2 == 0)
                        DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
                } break;
                case GUESSING:
                case GAMEPLAY:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
                    
                    // Draw lettercells
                    for (int r = 0; r < NUM_GUESSES; ++r){
                        for(int c = 0; c < NUM_LETTERS; ++c){
                            DrawLetterCell(&cells[r][c]);
                        }
                    }

                    // Draw keyboard
                    drawKeyboard(keyb);
                } break;
                case ENDING:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
                } break;
                default: break;
            }
        EndDrawing();
        // ------------------------------------------------------------
    }

    // De-Initialize
    // ----------------------------------------------------------------

    CloseWindow();
    releaseKeyboard(keyb);
    // ----------------------------------------------------------------
    return 0;
}