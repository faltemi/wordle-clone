#include "theme.h"
#include <stdlib.h>

static void DayTheme(Theme *t){
    t->curTheme = THEME_DAY;
    t->mainBackground = RAYWHITE;
    t->titleBackground = DARKBROWN;
    t->titleText = DARKGREEN;
    t->subText = DARKGRAY; // Title subtext, blinking text
    t->winText = DARKGREEN;
    t->loseText = DARKPURPLE;
    // LetterIcons
    t->normalBorder = LIGHTGRAY;
    t->beingGuessedBorder = DARKGRAY;
    t->normalFont = RAYWHITE;
    t->beingGuessedFont = BLACK;
    t->incorrectBackground = DARKGRAY;
    t->beingGuessedBackground = RAYWHITE;
    t->noGuessBackground = RAYWHITE;
    t->wrongPosBackground = YELLOW;
    t->correctBackground = GREEN;
    // These might just mirror letter icons
    t->keybBorder;
    t->keybBackground;
    t->keybFont;
    // Notifications
    t->notifBackground = BLACK;
    t->notifFont = RAYWHITE;
    // Settings panel
    t->settingsBackground = WHITE;
    t->settingsFade = BLACK;
    t->settingsText = BLACK;
    // Settings icon
    t->settingsIconBackground = RAYWHITE;
    t->settingsIconGear = GRAY;
    t->settingsIconGearInner = RAYWHITE;
    // Close panel icon
    t->closePanelBackground = RAYWHITE;
    t->closePanelSpokes = GRAY;
}

Theme *MakeTheme(){
    Theme *t = malloc(sizeof(Theme));
    DayTheme(t);
    return t;
}

void FreeTheme(Theme *t){
    free(t);
}

void CycleTheme(Theme *t){
    t->curTheme = (t->curTheme + 1) % THEME_END; // ToDo: Tie this to text in settings screen
    switch (t->curTheme){
        case THEME_DAY:
        {
            DayTheme(t);
        } break;
        case THEME_NIGHT:
        {
            // ToDo
        } break;
        default:
        {
            // ToDo: Log error
        } break;
    }
}