#include "cell.h"
#include <stddef.h>
#include <stdio.h>

static inline void DrawLetter(LetterCell *cell, Color fontColor){
    int posX = cell->bounds.x + (cell->bounds.width - MeasureText(cell->letter, cell->fontSize))/2;
    int posY = cell->bounds.y + (cell->bounds.height - cell->fontSize)/2;
    DrawText(cell->letter, posX, posY, cell->fontSize, fontColor);
}

void DrawLetterCell(LetterCell *cell){
    // Testing border
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
    if (border){
        borderSize = BORDER_SIZE;
        DrawRectangle(cell->bounds.x, cell->bounds.y, cell->bounds.width, cell->bounds.height, borderColor);
    }
    DrawRectangle(cell->bounds.x+borderSize, cell->bounds.y+borderSize, cell->bounds.width-borderSize*2, cell->bounds.height-borderSize*2, cellColor);

    if (cell->state != NO_GUESS && cell->letter){
        DrawLetter(cell, fontColor);
    }
}

void InitLetterCell(LetterCell *cell, Vector2 position, Vector2 size, int fontSize){
    cell->state = NO_GUESS;
    cell->fontSize = fontSize;
    cell->letter = NULL;
    cell->bounds = (Rectangle){ position.x, position.y, size.x, size.y };
}
