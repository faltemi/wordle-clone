#ifndef SETTINGS_PANEL_H
#define SETTINGS_PANEL_H

#include "raylib.h"
#include "gameState.h"
#include "icon.h"
#include "settingsState.h"

typedef struct SettingsPanel {
    Rectangle panelBounds;
    Icon *closeButton;
    //Icon *hardModeToggle;
    //Icon *themeSelector;
    float roundness;
} SettingsPanel;

SettingsPanel *MakeSettingsPanel(GameState *g);
void FreeSettingsPanel(SettingsPanel *s);
void DrawSettingsScreen(SettingsPanel *panel, GameState *state);
void ProcessSettingsInput(SettingsPanel *panel, GameState *state);
void ToggleSetting(SettingsState *settings, int settingIdx);

#endif // SETTINGS_PANEL_H