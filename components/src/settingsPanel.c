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

    // Theme selector in center of panel
    Rectangle themeBounds = {
        p->panelBounds.x + (p->panelBounds.width - 140) / 2,  // Center horizontally (120px wide)
        p->panelBounds.y + (p->panelBounds.height - 50) / 2,  // Center vertically (50px tall)
        140, 50
    };
    p->themeSelector = MakeIcon(ICON_THEME, themeBounds, g);
    // Hardmode toggle below theme selector
    Rectangle hardModeToggleBounds = {
        p->panelBounds.x + (p->panelBounds.width - 140) / 2,  // Center horizontally (120px wide)
        p->panelBounds.y + 75 + (p->panelBounds.height - 50) / 2,  // Center vertically (50px tall)
        140, 50
    };
    p->hardModeToggle = MakeIcon(ICON_HARD_MODE, hardModeToggleBounds, g);

    p->roundness = 0.1f;

    return p;
}

void FreeSettingsPanel(SettingsPanel *p){
    FreeIcon(p->closeButton);
    FreeIcon(p->themeSelector);
    FreeIcon(p->hardModeToggle);
    free(p);
}

void DrawSettingsScreen(SettingsPanel *panel, GameState *g){
    // Fade background overlay
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, Fade(g->theme->settingsFade, 0.5f));

    // Main panel with rounded corners
    DrawRectangleRounded(panel->panelBounds, panel->roundness, 10, g->theme->settingsBackground);

    // Title
    DrawText("SETTINGS", panel->panelBounds.x + 20, panel->panelBounds.y + 20, 32, g->theme->settingsText);

    // Close button (X in top-right)
    panel->closeButton->draw(panel->closeButton, g);

    // Theme selector in center
    panel->themeSelector->draw(panel->themeSelector, g);

    panel->hardModeToggle->draw(panel->hardModeToggle, g);
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

    // Handle theme selector click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), panel->themeSelector->bounds)) {
        panel->themeSelector->onClick(state);
    }

    // Handle hardmode toggle click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), panel->hardModeToggle->bounds)) {
        panel->hardModeToggle->onClick(state);
    }
}
