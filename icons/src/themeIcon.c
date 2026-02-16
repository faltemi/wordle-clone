#include "themeIcon.h"
#include "icon.h"
#include "theme.h"

ThemeIcon *MakeThemeIcon(Rectangle bounds){
    ThemeIcon *t = malloc(sizeof(ThemeIcon));
    t->bounds = bounds;
    return t;
}

void DrawThemeIcon(Icon *i, GameState *g){
    ThemeIcon *t = i->data.themeIcon;

    const char *themeText = "";
    switch(g->theme->curTheme){
        case THEME_DAY:
            themeText = "Day";
            break;
        case THEME_NIGHT:
            themeText = "Night";
            break;
        default:
            themeText = "???";
            break;
    }

    // Draw rounded rectangle background
    float roundness = 0.3f;
    int segments = 10;
    DrawRectangleRounded(t->bounds, roundness, segments, g->theme->themeIconBackground);

    // Draw text centered in bounds
    int fontSize = 20;
    int textWidth = MeasureText(themeText, fontSize);
    int textX = t->bounds.x + (t->bounds.width - textWidth) / 2;
    int textY = t->bounds.y + (t->bounds.height - fontSize) / 2;

    DrawText(themeText, textX, textY, fontSize, g->theme->themeIconText);
}

void ClickThemeIcon(GameState *g){
    CycleTheme(g->theme);
}