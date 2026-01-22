#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "keyboard.h"
#include "globals.h"
#include "gameGrid.h"

void DrawMainGameplayScreen(GameGrid *gameGrid, Keyboard *keyb, GameState *g);

#endif // DRAW_H