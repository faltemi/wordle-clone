#include "settingsPanel.h"
#include <math.h>
#include <stdlib.h>

SettingsPanel *MakeSettingsPanel(GameState *g){
    SettingsPanel *p = malloc(sizeof(SettingsPanel));

    // Calculate centered panel bounds based on screen size
    p->panelBounds = (Rectangle){
        g->screenWidth/2 - 250,
        g->screenHeight/2 - 200,
        500, 400
    };

    // Close button in top-right corner of panel
    Rectangle closeBtnBounds = {
        p->panelBounds.x + p->panelBounds.width - 40,  // 40px from right edge
        p->panelBounds.y + 10,                          // 10px from top edge
        30, 30                                          // 30x30 button
    };
    p->closeButton = MakeIcon(ICON_CLOSE, closeBtnBounds, g);

    p->roundness = 0.1f;

    return p;
}

void FreeSettingsPanel(SettingsPanel *p){
    FreeIcon(p->closeButton);
    free(p);
}

void DrawSettingsScreen(SettingsPanel *panel, GameState *state){
    // Fade background overlay
    DrawRectangle(0, 0, state->screenWidth, state->screenHeight, Fade(BLACK, 0.5f));

    // Main panel with rounded corners
    DrawRectangleRounded(panel->panelBounds, panel->roundness, 10, WHITE);

    // Title
    DrawText("SETTINGS", panel->panelBounds.x + 20, panel->panelBounds.y + 20, 32, BLACK);

    // Close button (X in top-right)
    panel->closeButton->draw(panel->closeButton, state);

    // ToDo: Setting rows with toggle switches

}

void ProcessSettingsInput(SettingsPanel *panel, GameState *state){
    // Close settings with ESC key
    if (IsKeyPressed(KEY_ESCAPE)) {
        state->gameScreen = GAMEPLAY;
        return;
    }

    // Handle close button click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), panel->closeButton->bounds)) {
        panel->closeButton->onClick(state);
    }
}

void ToggleSetting(SettingsState *settings, int settingIdx){

}