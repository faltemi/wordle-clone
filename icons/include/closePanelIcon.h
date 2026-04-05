#ifndef CLOSE_PANEL_ICON_H
#define CLOSE_PANEL_ICON_H

#include "raylib.h"
#include "gameState.h"
#include <stdlib.h>

typedef struct Icon Icon;

typedef struct ClosePanelIcon {
    Rectangle bounds;
    Vector2 center;
    float spokeLength;
    float spokeAngle;
    Vector2 spokeCenter;
    Rectangle spoke;
} ClosePanelIcon;

ClosePanelIcon *MakeClosePanelIcon(Rectangle bounds);
void DrawClosePanelIcon(Icon *i, GameState *g);
void ClickClosePanelIcon(GameState *g);

#endif // CLOSE_PANEL_ICON_H