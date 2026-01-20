#include "icon.h"

static void MakeSettings(Icon *i, Rectangle bounds, GameState *g){
    i->type = ICON_SETTINGS;
    i->bounds = bounds;
    i->data.settings = MakeSettingsIcon(bounds);
    i->onClick = &ClickSettingsIcon;
    i->draw = &DrawSettingsIcon;
}

static void MakeLetter(Icon *i, Rectangle bounds, GameState *g){
    i->type = ICON_LETTER;
    i->bounds = bounds;
    i->data.letterIcon = MakeLetterIcon(bounds, g);
    i->draw = &DrawLetterIcon;
}

// Icon factory
Icon *MakeIcon(IconType type, Rectangle bounds, GameState *g){
    Icon *i = malloc(sizeof(Icon));
    switch(type){
        case ICON_SETTINGS:
            MakeSettings(i, bounds, g);
            break;
        case ICON_LETTER:
            MakeLetter(i, bounds, g);
            break;
        default: break;
    }
    return i;
}

// ToDo: On click event, replace usage in main, then add struct to contain Icon
// Should notif mgr be in gamestate too?

void FreeIcon(Icon *i){
    switch(i->type){
        case ICON_SETTINGS:
        {
            free(i->data.settings);
        } break;
        case ICON_LETTER:
        {
            free(i->data.letterIcon);
        } break;
        default: break;
    }
    free(i);
}