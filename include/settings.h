#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"

typedef struct SettingsIcon {
    Rectangle bounds;
    Vector2 center;
    float spokeLength;
    float spokeAngle;
    Vector2 spokeCenter;
    Rectangle spoke;
} SettingsIcon;

void InitSettingsIcon(SettingsIcon *s, Rectangle bounds);
void DrawSettingsIcon(SettingsIcon *s);
void DrawSettingsScreen();

#endif // SETTINGS_H