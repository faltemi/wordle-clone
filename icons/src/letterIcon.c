#include "letterIcon.h"
#include "icon.h"
#include "globals.h"

LetterIcon *MakeLetterIcon(Rectangle bounds, GameState *g){
    LetterIcon *l = malloc(sizeof(LetterIcon));
    l->state = NO_GUESS;
    l->fontSize = g->cellFontSize;
    l->letter[0] = '\0';
    l->bounds = bounds;
    return l;
}

static inline void DrawLetter(LetterIcon *l, Color fontColor, float xSkew){
    int posX = (l->bounds.x + xSkew) + (l->bounds.width - MeasureText(l->letter, l->fontSize))/2;
    int posY = l->bounds.y + (l->bounds.height - l->fontSize)/2;
    DrawText(l->letter, posX, posY, l->fontSize, fontColor);
}

void DrawLetterIcon(Icon *i, GameState *g){
    int tmpSkew = g->shakeSkew;
    g->shakeSkew = 0;
    DrawLetterIconWithSkew(i->data.letterIcon, g);
    g->shakeSkew = tmpSkew;
}

void DrawLetterIconWithSkew(LetterIcon *l, GameState *g){
    bool border = false;
    Color borderColor = g->theme->normalBorder;
    Color letterIconColor = g->theme->noGuessBackground;
    Color fontColor = g->theme->normalFont;
    int borderSize = 0;
    switch(l->state){
        case NO_GUESS:
        {
            border = true;
            borderColor = g->theme->normalBorder;
            letterIconColor = g->theme->noGuessBackground;
        } break;
        case WRONG_POS:
        {
            border = false;
            letterIconColor = g->theme->wrongPosBackground;
            fontColor = g->theme->normalFont;
        } break;
        case CORRECT:
        {
            border = false;
            letterIconColor = g->theme->correctBackground;
            fontColor = g->theme->normalFont;
        } break;
        case INCORRECT:
        {
            border = false;
            letterIconColor = g->theme->incorrectBackground;
            fontColor = g->theme->normalFont;
        } break;
        case BEING_GUESSED:
        {
            border = true;
            borderColor = g->theme->beingGuessedBorder;
            letterIconColor = g->theme->beingGuessedBackground;
            fontColor = g->theme->beingGuessedFont;
        } break;
        default: break;
    }

    float cellX = l->bounds.x + g->shakeSkew;
    if (border){
        borderSize = g->cellBorderSize;
        DrawRectangle(cellX, l->bounds.y, l->bounds.width, l->bounds.height, borderColor);
    }
    DrawRectangle(cellX+borderSize, l->bounds.y+borderSize, l->bounds.width-borderSize*2, l->bounds.height-borderSize*2, letterIconColor);

    if (l->state != NO_GUESS){
        DrawLetter(l, fontColor, g->shakeSkew);
    }
}