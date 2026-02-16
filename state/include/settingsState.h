#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include <stdbool.h>

typedef struct SettingsState {
    bool hardModeEnabled;
    int themeIdx; // ToDo: Add light and dark theme
    bool soundEnabled;
} SettingsState;

SettingsState *MakeDefaultSettingsState();
void FreeSettingsState(SettingsState *s);

#endif // SETTINGS_STATE_H