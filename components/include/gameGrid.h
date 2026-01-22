#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "globals.h"
#include "icon.h"

typedef struct GameGrid {
    Icon *letterIcons[NUM_GUESSES][NUM_LETTERS];
} GameGrid;

void AddLetter(GameGrid *gameGrid, char letter, GameState *g);
void DeleteLetter(GameGrid *gameGrid, GameState *g);
GameGrid *MakeGameGrid(GameState *g);
void DrawGameGrid(GameGrid *grid, GameState *g);
void ShakeRow(GameGrid *grid, GameState *g);
void ResetGrid(GameGrid *grid);
void FreeGameGrid(GameGrid *grid);

#endif // GAME_GRID_H