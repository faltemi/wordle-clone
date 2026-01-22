#include "raylib.h"
#include "keyboard.h"
#include "inputProcessing.h"
#include "draw.h"
#include "guessing.h"
#include "globals.h"
#include "wordList.h"
#include "notificationManager.h"
#include "settings.h"
#include "icon.h"
#include "gameState.h"
#include "gameGrid.h"
#include <stdio.h>

// ToDo: Consolidate into draw.c
static inline void ProcessNotifications(NotificationManager *nMgr, GameGrid *grid, GameState *g){
    if(DrawNotifications(nMgr, g) && nMgr->rowShake_s > 0){
        ShakeRow(grid, g);
    }
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    SetRandomSeed(1234); // ToDo: make this truly random
    GameState *gameState = MakeDefaultGameState();

    InitWindow(gameState->screenWidth, gameState->screenHeight, gameState->windowTitle);
    // NOTE: Load resources (textures, fonts, audio) after Window initialization

    // ToDo: Do these belong in game state?
    NotificationManager notificationManager;
    SetNotification(&notificationManager, NOTIFY_NONE);
    // ToDo: Icon struct
    Icon *settingsIcon = MakeIcon(ICON_SETTINGS, (Rectangle){gameState->screenWidth-50, 0, 50, 50}, gameState);
    GameGrid *gameGrid = MakeGameGrid(gameState);

    // ToDo: Actually use cell params to make keyb
    Keyboard *keyb = CreateKeyboard(
        gameState,
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
        gameState->framesCounter++;
        switch (gameState->gameScreen){
            case LOGO:
            {
                // After 3 seconds, change to title screen
                if(gameState->framesCounter > 180){
                    gameState->gameScreen = TITLE;
                    gameState->framesCounter = 0;
                }
            } break;
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER)) gameState->gameScreen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
                ProcessKeyboardInputs(gameGrid, &notificationManager, gameState);
                ProcessMouseInputs(gameGrid, keyb, &notificationManager, settingsIcon, gameState);
                UpdateNotification(&notificationManager, GetFrameTime());
            } break;
            case GUESSING:
            {
                ProcessGuess(gameGrid, gameState);
                UpdateNotification(&notificationManager, GetFrameTime());
            } break;
            case WIN:
            case LOSE:
            {
                UpdateNotification(&notificationManager, GetFrameTime());
                if(IsKeyPressed(KEY_ENTER)){
                    // Reset game
                    RestartGame(gameState);

                    // Reset keyboard

                    // Reset cells
                    ResetGrid(gameGrid);
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
                    if ((gameState->framesCounter/30)%2 == 0)
                        DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
                } break;
                case GUESSING:
                case GAMEPLAY:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    ProcessNotifications(&notificationManager, gameGrid, gameState);
                } break;
                case WIN:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    
                    DrawText("WELL DONE!", (GetScreenWidth() - MeasureText("WELL DONE!", gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, DARKGREEN);
                    if((gameState->framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, gameGrid, gameState);
                } break;
                case LOSE:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    const char* endMessage = TextFormat("SO CLOSE! IT WAS %s.", gameState->targetWord);
                    DrawText(endMessage, (GetScreenWidth() - MeasureText(endMessage, gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, DARKPURPLE);
                    if((gameState->framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, DARKGRAY);
                    }
                    ProcessNotifications(&notificationManager, gameGrid, gameState);
                } break;
                case SETTINGS:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    DrawSettingsScreen();
                }
                default: break;
            }
        EndDrawing();
        // ------------------------------------------------------------
    }

    // De-Initialize
    // ----------------------------------------------------------------

    CloseWindow();
    ReleaseKeyboard(keyb);
    FreeGameGrid(gameGrid);
    FreeIcon(settingsIcon);
    FreeGameState(gameState);
    // ----------------------------------------------------------------
    return 0;
}