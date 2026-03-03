#include "hardModeIcon.h"
#include "icon.h"

HardModeIcon *MakeHardModeIcon(Rectangle bounds){
    HardModeIcon *h = malloc(sizeof(HardModeIcon));
    h->bounds = bounds;
    return h;
}

void DrawHardModeIcon(Icon *i, GameState *g){
    HardModeIcon *h = i->data.hardModeIcon;

    const char *difficultyText = "";
    if(g->isHardMode){
        difficultyText = "Hard Mode";
    }
    else{
        difficultyText = "Normal Mode";
    }

    // Draw rounded rectangle background
    float roundness = 0.3f;
    int segments = 10;
    // ToDo: Address reusing themeicon background
    DrawRectangleRounded(h->bounds, roundness, segments, g->theme->themeIconBackground);

    // Draw text centered in bounds
    int fontSize = 20;
    int textWidth = MeasureText(difficultyText, fontSize);
    int textX = h->bounds.x + (h->bounds.width - textWidth) / 2;
    int textY = h->bounds.y + (h->bounds.height - fontSize) / 2;

    DrawText(difficultyText, textX, textY, fontSize, g->theme->themeIconText);
}

void ClickHardModeIcon(GameState *g){
    g->isHardMode = !g->isHardMode;
}
