#ifndef ICON_H
#define ICON_H

#include "raylib.h"
#include "settingsIcon.h"
#include "letterIcon.h"
#include "gameState.h"
#include <stdlib.h>

// Forward declaration for self reference in draw method
typedef struct Icon Icon;

typedef enum IconType {
    ICON_SETTINGS,
    ICON_CLOSE,
    ICON_HARD_MODE,
    ICON_THEME,
    ICON_LETTER,
    ICON_KEYB_LETTER
} IconType;

typedef struct Icon {
    IconType type;
    Rectangle bounds; // Used for drawing contents relative to bounding range
    void (*draw)(Icon *, GameState *);
    void (*onClick)(GameState *); // ToDo: Instead of handling click event, have enum to determine the event
    union{
        SettingsIcon *settings;
        LetterIcon *letterIcon;
    } data;
} Icon;

Icon *MakeIcon(IconType type, Rectangle bounds, GameState *g);
void FreeIcon(Icon *i);

#endif // ICON_H