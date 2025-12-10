#include "raylib.h"
#include "cell.h"

#define NUM_GUESSES         6
#define NUM_LETTERS         5
#define CELL_SIZE           50
#define CELL_Y_OFFSET       50
#define CELL_X_OFFSET       150
#define CELL_PADDING        5
#define LETTER_SIZE         20

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

// Position calculation for letter cells
static inline void InitLetterCellAt(LetterCell *cell, int row, int col) {
    // Center with respect to padding (which isnt ba)
    const int paddingX = col == 0 ? 0 : CELL_PADDING;
    const int paddingY = row == 0 ? 0 : CELL_PADDING;

    const int totalW = NUM_LETTERS*CELL_SIZE + CELL_PADDING*(NUM_LETTERS-1);
    const int offsetX = (GetScreenWidth() - totalW)/2;

    const int posX = col*(CELL_SIZE + paddingX) + offsetX;
    const int posY = row*(CELL_SIZE + paddingY) + CELL_Y_OFFSET;

    InitLetterCell(cell, CELL_SIZE, CELL_SIZE, posX, posY, LETTER_SIZE);
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    // Window setup parameters
    const int screenWidth = 800;
    const int screenHeight = 600;
    const char *windowTitle = "Wordle Clone";

    InitWindow(screenWidth, screenHeight, windowTitle);
    // NOTE: Load resources (textures, fonts, audio) after Window initialization
    
    // Setup initial game state
    GameScreen screen = TITLE;

    int framesCounter = 0;
    int gameResult = -1;

    LetterCell cells[NUM_GUESSES][NUM_LETTERS] = { 0 };

    // Initialize letter cells
    for (int r = 0; r < NUM_GUESSES; r++){
        for (int c = 0; c < NUM_LETTERS; c++){
            InitLetterCellAt(&cells[r][c], r, c);
        }
    }

    LetterCell *keyboard[3] = { 0 };
    initKeyboard(&keyboard);

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
                case GAMEPLAY:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
                    
                    // Draw lettercells
                    for (int r = 0; r < NUM_GUESSES; ++r){
                        for(int c = 0; c < NUM_LETTERS; ++c){
                            DrawLetterCell(&cells[r][c]);
                        }
                    }
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
    // ----------------------------------------------------------------
    return 0;
}