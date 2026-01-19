#ifndef ICON_H
#define ICON_H

#include "raylib.h"
#include "settingsIcon.h"
#include <stdlib.h>

// Forward declaration for self reference in draw method
typedef struct Icon Icon;

typedef enum IconType {
    ICON_SETTINGS,
    ICON_CLOSE,
    ICON_HARD_MODE,
    ICON_THEME
} IconType;

typedef struct Icon {
    IconType type;
    Rectangle bounds; // Used for drawing contents relative to bounding range
    void (*draw)(Icon *);
    void (*onClick)();// Add gamestate
    union{
        SettingsIcon *settings;
    } data;
} Icon;

Icon *MakeIcon(IconType type, Rectangle bounds);
void FreeIcon(Icon *i);

#endif // ICON_H