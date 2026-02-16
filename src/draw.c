#include "draw.h"

void DrawMainGameplayScreen(GameGrid *gameGrid, Keyboard *keyb, GameState *g){
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, g->theme->mainBackground);
    DrawGameGrid(gameGrid, g);
    DrawKeyboard(keyb, g);
}