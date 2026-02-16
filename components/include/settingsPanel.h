#ifndef SETTINGS_PANEL_H
#define SETTINGS_PANEL_H

#include "raylib.h"
#include "gameState.h"
#include "settingsState.h"

void DrawSettingsScreen();
void ProcessSettingsInput(GameState *state);
void ToggleSetting(SettingsState *settings, int settingIdx);

#endif // SETTINGS_PANEL_H