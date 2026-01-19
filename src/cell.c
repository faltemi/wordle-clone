#include "cell.h"
#include "globals.h"
#include <stddef.h>

static inline void DrawLetter(LetterCell *cell, Color fontColor, float xSkew){
    int posX = (cell->bounds.x + xSkew) + (cell->bounds.width - MeasureText(cell->letter, cell->fontSize))/2;
    int posY = cell->bounds.y + (cell->bounds.height - cell->fontSize)/2;
    DrawText(cell->letter, posX, posY, cell->fontSize, fontColor);
}

void DrawLetterCell(LetterCell *cell){
    DrawLetterCellWithSkew(cell, 0);
}

// Skew allows for row shaking visual
void DrawLetterCellWithSkew(LetterCell *cell, float xSkew){
    bool border = false;
    Color borderColor = LIGHTGRAY;
    Color cellColor = RAYWHITE;
    Color fontColor = RAYWHITE;
    int borderSize = 0;
    switch(cell->state){
        case NO_GUESS:
        {
            border = true;
            borderColor = LIGHTGRAY;
            cellColor = RAYWHITE;
        } break;
        case WRONG_POS:
        {
            border = false;
            cellColor = YELLOW;
            fontColor = RAYWHITE;
        } break;
        case CORRECT:
        {
            border = false;
            cellColor = GREEN;
            fontColor = RAYWHITE;
        } break;
        case INCORRECT:
        {
            border = false;
            cellColor = DARKGRAY;
            fontColor = RAYWHITE;
        } break;
        case BEING_GUESSED:
        {
            border = true;
            borderColor = DARKGRAY;
            cellColor = RAYWHITE;
            fontColor = BLACK;
        } break;
        case KEYBOARD:
        {
            border = true;
            borderColor = DARKGRAY;
            cellColor = RAYWHITE;
            fontColor = BLACK;
        } break;
        default: break;
    }

    float cellX = cell->bounds.x + xSkew;
    if (border){
        borderSize = BORDER_SIZE;
        DrawRectangle(cellX, cell->bounds.y, cell->bounds.width, cell->bounds.height, borderColor);
    }
    DrawRectangle(cellX+borderSize, cell->bounds.y+borderSize, cell->bounds.width-borderSize*2, cell->bounds.height-borderSize*2, cellColor);

    if (cell->state != NO_GUESS){
        DrawLetter(cell, fontColor, xSkew);
    }
}

void InitLetterCell(LetterCell *cell, Vector2 position, Vector2 size, int fontSize){
    cell->state = NO_GUESS;
    cell->fontSize = fontSize;
    cell->letter[0] = '\0';
    cell->bounds = (Rectangle){ position.x, position.y, size.x, size.y };
}

// Position calculation for letter cells
void InitLetterCellAt(LetterCell *cell, Vector2 position) {
    // Center with respect to padding
    const int paddingX = position.x == 0 ? 0 : CELL_PADDING;
    const int paddingY = position.y == 0 ? 0 : CELL_PADDING;

    const int totalW = NUM_LETTERS*CELL_SIZE + CELL_PADDING*(NUM_LETTERS-1);
    const int offsetX = (GetScreenWidth() - totalW)/2;

    const int posX = position.x*(CELL_SIZE + paddingX) + offsetX;
    const int posY = position.y*(CELL_SIZE + paddingY) + CELL_Y_OFFSET;

    InitLetterCell(cell, (Vector2){posX, posY}, (Vector2){CELL_SIZE, CELL_SIZE}, LETTER_SIZE);
}
