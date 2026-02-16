#ifndef THEME_H
#define THEME_H

#include "raylib.h"

typedef enum ThemeSelection {
    THEME_DAY,
    THEME_NIGHT,
    THEME_END // Keep this at the end
} ThemeSelection;

typedef struct Theme {
    ThemeSelection curTheme;
    Color mainBackground;
    Color titleBackground;
    Color titleText;
    Color subText; // Title subtext, blinking text
    Color winText;
    Color loseText;
    // LetterIcons
    Color normalBorder;
    Color beingGuessedBorder;
    Color normalFont;
    Color beingGuessedFont;
    Color incorrectBackground;
    Color beingGuessedBackground;
    Color noGuessBackground;
    Color wrongPosBackground;
    Color correctBackground;
    // These might just mirror letter icons
    Color keybBorder;
    Color keybBackground;
    Color keybFont;
    // Notifications
    Color notifBackground;
    Color notifFont;
    // Settings panel
    Color settingsBackground;
    Color settingsFade;
    Color settingsText;
    // Settings icon
    Color settingsIconBackground;
    Color settingsIconGear;
    Color settingsIconGearInner;
    // Close panel icon
    Color closePanelBackground;
    Color closePanelSpokes;
    // Theme icon
    Color themeIconBackground;
    Color themeIconText;

} Theme;

Theme *MakeTheme();
void FreeTheme(Theme *t);
void CycleTheme(Theme *t);


#endif // THEME_H