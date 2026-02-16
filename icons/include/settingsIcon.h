#ifndef SETTINGS_ICON_H
#define SETTINGS_ICON_H

#include "raylib.h"
#include "gameState.h"
#include <stdlib.h>

typedef struct Icon Icon;

typedef struct SettingsIcon {
    Rectangle bounds;
    Vector2 center;
    float spokeLength;
    float spokeAngle;
    Vector2 spokeCenter;
    Rectangle spoke;
} SettingsIcon;

SettingsIcon *MakeSettingsIcon(Rectangle bounds);
void DrawSettingsIcon(Icon *i, GameState *g);
void ClickSettingsIcon(GameState *g);

#endif // SETTINGS_ICON_H