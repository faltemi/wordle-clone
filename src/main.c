#include "raylib.h"
#include "keyboard.h"
#include "inputProcessing.h"
#include "draw.h"
#include "guessing.h"
#include "globals.h"
#include "wordList.h"
#include "notificationManager.h"
#include "settingsPanel.h"
#include "icon.h"
#include "gameState.h"
#include "gameGrid.h"
#include <stdio.h>

// ToDo: Consolidate into draw.c
static inline void ProcessNotifications(NotificationManager *nMgr, GameGrid *grid, GameState *g){
    if(DrawNotifications(nMgr, g) && nMgr->rowShake_s > 0){
        ShakeRow(grid, g, nMgr->rowShake_s);
    }
}

int main(){
    // Initialization
    // ----------------------------------------------------------------
    // SetRandomSeed(1234); // ToDo: make this truly random
    GameState *gameState = MakeDefaultGameState();

    InitWindow(gameState->screenWidth, gameState->screenHeight, gameState->windowTitle);
    SetExitKey(KEY_NULL);

    // ToDo: Do these belong in game state?
    NotificationManager notificationManager;
    SetNotification(&notificationManager, NOTIFY_NONE);
    // ToDo: Icon struct
    Icon *settingsIcon = MakeIcon(ICON_SETTINGS, (Rectangle){gameState->screenWidth-50, 0, 50, 50}, gameState);
    GameGrid *gameGrid = MakeGameGrid(gameState);

    // ToDo: Actually use cell params to make keyb
    Keyboard *keyb = CreateKeyboard(gameState);

    SettingsPanel *settingsPanel = MakeSettingsPanel(gameState);

    // Desired framerate
    SetTargetFPS(60);
    // ----------------------------------------------------------------

    // Main loop
    while(!WindowShouldClose()){
        // Update
        // ------------------------------------------------------------
        gameState->framesCounter++;
        switch (gameState->gameScreen){
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
                ProcessGuess(gameGrid, gameState, keyb);
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
                    ResetKeyboard(keyb);

                    // Reset cells
                    ResetGrid(gameGrid);
                }
            } break;
            case SETTINGS:
            {
                ProcessSettingsInput(settingsPanel, gameState);
            } break;
            default: break;
        }
        // ------------------------------------------------------------


        // Draw
        // ------------------------------------------------------------
        BeginDrawing();
            ClearBackground(gameState->theme->mainBackground);
            switch(gameState->gameScreen){
                case TITLE:
                {
                    DrawRectangle(0, 0, gameState->screenWidth, gameState->screenHeight, gameState->theme->titleBackground);
                    DrawText("\"WORDLE\"", (GetScreenWidth() - MeasureText("\"WORDLE\"", 40))/2, GetScreenHeight()/2, 40, gameState->theme->titleText);
                    // Every half second toggle text (60 fps)
                    if ((gameState->framesCounter/30)%2 == 0)
                        DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, gameState->theme->subText);
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
                    
                    DrawText("WELL DONE!", (GetScreenWidth() - MeasureText("WELL DONE!", gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, gameState->theme->winText);
                    if((gameState->framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, gameState->theme->subText);
                    }
                    ProcessNotifications(&notificationManager, gameGrid, gameState);
                } break;
                case LOSE:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    const char* endMessage = TextFormat("SO CLOSE! IT WAS %s.", gameState->targetWord);
                    DrawText(endMessage, (GetScreenWidth() - MeasureText(endMessage, gameState->endTextSize))/2, gameState->endTextOffsetY, gameState->endTextSize, gameState->theme->loseText);
                    if((gameState->framesCounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to try a new word.", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to try a new word.", 20)/2, GetScreenHeight()/2 + gameState->restartOffsetY, gameState->restartTextSize, gameState->theme->subText);
                    }
                    ProcessNotifications(&notificationManager, gameGrid, gameState);
                } break;
                case SETTINGS:
                {
                    DrawMainGameplayScreen(gameGrid, keyb, gameState);
                    settingsIcon->draw(settingsIcon, gameState); // ToDo: Struct for gameplay icons
                    DrawSettingsScreen(settingsPanel, gameState);
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
    FreeSettingsPanel(settingsPanel);
    FreeIcon(settingsIcon);
    FreeGameState(gameState);
    // ----------------------------------------------------------------
    return 0;
}