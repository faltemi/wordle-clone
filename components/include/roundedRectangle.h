#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include "raylib.h"
#include <stdlib.h>

typedef struct RoundedRectangle {
    float roundness;
    float width;
    float height;
    float segments;
    float lineThick;
    Rectangle rec;
} RoundedRectangle;

void drawRec(RoundedRectangle *rec){
    DrawRectangleRounded(rec->rec, rec->roundness, (int)rec->segments, Fade(MAROON, 0.2f));
}

RoundedRectangle *makeRec(){
    RoundedRectangle *rec = malloc(sizeof(RoundedRectangle));
    rec->roundness = 0.2f;
    rec->width = 200.0f;
    rec->height = 100.0f;
    rec->segments = 0.0f;
    rec->rec = {((float)GetScreenWidth() - rec->width - 250)/2, (GetScreenHeight() - rec->height)/2.0f, (float)rec->width, (float)rec->height};
    return rec;
}
#endif // ROUNDED_RECTANGLE_H