#include "icon.h"

static void MakeSettings(Icon *i, Rectangle bounds, GameState *g){
    (void)g;
    i->type = ICON_SETTINGS;
    i->bounds = bounds;
    i->data.settings = MakeSettingsIcon(bounds);
    i->onClick = &ClickSettingsIcon;
    i->draw = &DrawSettingsIcon;
}

static void MakePanelClose(Icon *i, Rectangle bounds, GameState *g){
    (void)g;
    i->type = ICON_CLOSE;
    i->bounds = bounds;
    i->data.closePanel = MakeClosePanelIcon(bounds);
    i->onClick = &ClickClosePanelIcon;
    i->draw = &DrawClosePanelIcon;
}

static void MakeLetter(Icon *i, Rectangle bounds, GameState *g){
    i->type = ICON_LETTER;
    i->bounds = bounds;
    i->data.letterIcon = MakeLetterIcon(bounds, g);
    i->draw = &DrawLetterIcon;
    i->onClick = NULL;
}

static void MakeKeyboardLetter(Icon *i, Rectangle bounds, GameState *g){
    i->type = ICON_KEYB_LETTER;
    i->bounds = bounds;
    i->data.letterIcon = MakeLetterIcon(bounds, g);
    i->draw = DrawLetterIcon;
    // ToDo: Add on click
}

// Icon factory
Icon *MakeIcon(IconType type, Rectangle bounds, GameState *g){
    Icon *i = malloc(sizeof(Icon));
    switch(type){
        case ICON_CLOSE:
            MakePanelClose(i, bounds, g);
            break;
        case ICON_SETTINGS:
            MakeSettings(i, bounds, g);
            break;
        case ICON_LETTER:
            MakeLetter(i, bounds, g);
            break;
        case ICON_KEYB_LETTER:
            MakeKeyboardLetter(i, bounds, g);
            break;
        default: break;
    }
    return i;
}

// ToDo: On click event, replace usage in main, then add struct to contain Icon
// Should notif mgr be in gamestate too?

void FreeIcon(Icon *i){
    switch(i->type){
        case ICON_CLOSE:
        {
            free(i->data.closePanel);
        } break;
        case ICON_SETTINGS:
        {
            free(i->data.settings);
        } break;
        case ICON_KEYB_LETTER:
        case ICON_LETTER:
        {
            free(i->data.letterIcon);
        } break;
        default: break;
    }
    free(i);
}