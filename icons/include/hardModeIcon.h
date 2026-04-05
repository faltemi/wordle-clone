#ifndef HARD_MODE_ICON_H
#define HARD_MODE_ICON_H

#include "raylib.h"
#include "gameState.h"
#include <stdlib.h>

typedef struct Icon Icon;

typedef struct HardModeIcon {
    Rectangle bounds;
} HardModeIcon;

HardModeIcon *MakeHardModeIcon(Rectangle bounds);
void DrawHardModeIcon(Icon *i, GameState *g);
void ClickHardModeIcon(GameState *g);

#endif // HARD_MODE_ICON_H