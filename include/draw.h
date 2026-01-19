#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "keyboard.h"
#include "globals.h"

void DrawMainGameplayScreen(LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, int screenWidth, int screenHeight);
void DrawRowShake(LetterCell cells[NUM_GUESSES][NUM_LETTERS], int row, int framesCounter);

#endif // DRAW_H