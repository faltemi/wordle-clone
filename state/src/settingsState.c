#include "settingsState.h"

#include <stdlib.h>

SettingsState *MakeDefaultSettingsState(){
    SettingsState *s = malloc(sizeof(SettingsState));
    s->hardModeEnabled = false;
    s->soundEnabled = true;
    s->themeIdx = 0;
    return s;
}

void FreeSettingsState(SettingsState *s){
    free(s);
}