#ifndef CELL_H
#define CELL_H

#include "raylib.h"
#include "gameState.h"

#define BORDER_SIZE 2

typedef enum CellState {
    KEYBOARD // This is for when the cells are reused for the on screen keyboard
} CellState;

typedef struct LetterCell {
    Rectangle bounds;
    char letter[8];
    int fontSize;
    CellState state;
} LetterCell;


void DrawLetterCell(LetterCell *cell);
void DrawLetterCellWithSkew(LetterCell *cell, float ySkew);
void InitLetterCell(LetterCell *cell, Vector2 position, Vector2 size, int fontSize);
void InitLetterCellAt(LetterCell *cell, Vector2 position, GameState *g);
#endif // CELL_H