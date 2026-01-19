#include "icon.h"

static void MakeSettings(Icon *i, Rectangle bounds){
    i->type = ICON_SETTINGS;
    i->bounds = bounds;
    i->data.settings = MakeSettingsIcon(bounds);
    i->draw = &DrawSettingsIcon;
}

// Icon factory
Icon *MakeIcon(IconType type, Rectangle bounds){
    Icon *i = malloc(sizeof(Icon));
    switch(type){
        case ICON_SETTINGS:
            MakeSettings(i, bounds);
            break;
        default: break;
    }
    return i;
}

void FreeIcon(Icon *i){
    switch(i->type){
        case ICON_SETTINGS:
        {
            free(i->data.settings);
        } break;
        default: break;
    }
    free(i);
}