#include "theme.h"
#include <stdlib.h>

#define MUSTARDYELLOW (Color){ 201, 180, 88, 255 }
#define CORRECTGREEN (Color){ 106, 170, 100, 255 }

static void DayTheme(Theme *t){
    t->curTheme = THEME_DAY;
    t->mainBackground = RAYWHITE;
    t->titleBackground = DARKBROWN;
    t->titleText = DARKGREEN;
    t->subText = DARKGRAY; // Title subtext, blinking text
    t->winText = CORRECTGREEN;
    t->loseText = DARKPURPLE;
    // LetterIcons
    t->normalBorder = LIGHTGRAY;
    t->beingGuessedBorder = DARKGRAY;
    t->normalFont = RAYWHITE;
    t->beingGuessedFont = BLACK;
    t->incorrectBackground = DARKGRAY;
    t->beingGuessedBackground = RAYWHITE;
    t->noGuessBackground = RAYWHITE;
    t->wrongPosBackground = MUSTARDYELLOW;
    t->correctBackground = CORRECTGREEN;
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
    // Theme icon
    t->themeIconBackground = RAYWHITE;
    t->themeIconText = BLACK;
}

static void NightTheme(Theme *t){
    t->curTheme = THEME_NIGHT;
    t->mainBackground = (Color){ 18, 18, 19, 255 };
    t->titleBackground = (Color){ 18, 18, 19, 255 };
    t->titleText = (Color){ 215, 218, 220, 255 };
    t->subText = (Color){ 129, 131, 132, 255 };
    t->winText = CORRECTGREEN;
    t->loseText = (Color){ 186, 85, 211, 255 };
    // LetterIcons
    t->normalBorder = (Color){ 58, 58, 60, 255 };
    t->beingGuessedBorder = (Color){ 86, 87, 88, 255 };
    t->normalFont = RAYWHITE;
    t->beingGuessedFont = RAYWHITE;
    t->incorrectBackground = (Color){ 58, 58, 60, 255 };
    t->beingGuessedBackground = (Color){ 18, 18, 19, 255 };
    t->noGuessBackground = (Color){ 18, 18, 19, 255 };
    t->wrongPosBackground = MUSTARDYELLOW;
    t->correctBackground = CORRECTGREEN;
    // These might just mirror letter icons
    t->keybBorder;
    t->keybBackground;
    t->keybFont;
    // Notifications
    t->notifBackground = RAYWHITE;
    t->notifFont = BLACK;
    // Settings panel
    t->settingsBackground = (Color){ 18, 18, 19, 255 };
    t->settingsFade = BLACK;
    t->settingsText = RAYWHITE;
    // Settings icon
    t->settingsIconBackground = (Color){ 18, 18, 19, 255 };
    t->settingsIconGear = (Color){ 129, 131, 132, 255 };
    t->settingsIconGearInner = (Color){ 18, 18, 19, 255 };
    // Close panel icon
    t->closePanelBackground = (Color){ 18, 18, 19, 255 };
    t->closePanelSpokes = (Color){ 129, 131, 132, 255 };
    // Theme icon
    t->themeIconBackground = (Color){ 18, 18, 19, 255 };
    t->themeIconText = RAYWHITE;
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
            NightTheme(t);
        } break;
        default:
        {
            // ToDo: Log error
        } break;
    }
}