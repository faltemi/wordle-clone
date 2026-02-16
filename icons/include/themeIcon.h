#ifndef THEME_ICON_H
#define THEME_ICON_H

#include "raylib.h"
#include "gameState.h"
#include <stdlib.h>

typedef struct Icon Icon;

typedef struct ThemeIcon {
    Rectangle bounds;
} ThemeIcon;

ThemeIcon *MakeThemeIcon(Rectangle bounds);
void DrawThemeIcon(Icon *i, GameState *g);
void ClickThemeIcon(GameState *g);

#endif // THEME_ICON_H