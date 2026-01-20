#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "globals.h"
#include "icon.h"

typedef struct GameGrid {
    Icon *letterIcons[NUM_GUESSES][NUM_LETTERS];
} GameGrid;

GameGrid *MakeGameGrid(GameState *g);
void DrawGameGrid(GameGrid *grid, GameState *g);
void ShakeRow(GameGrid *grid, GameState *g);
void ResetGrid(GameGrid *grid);
GameGrid *FreeGameGrid(GameGrid *grid);

#endif // GAME_GRID_H