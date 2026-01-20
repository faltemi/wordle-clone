#include "settingsIcon.h"
#include "icon.h"
#include <math.h>

SettingsIcon *MakeSettingsIcon(Rectangle bounds){
    SettingsIcon *s = malloc(sizeof(SettingsIcon));
    s->bounds = bounds;
    s->center = (Vector2) {bounds.x + bounds.height/2, bounds.y + bounds.width/2};
    s->spokeLength = sqrt(pow(bounds.height, 2.0) + pow(bounds.width, 2.0))*0.6;
    s->spokeAngle = 60.0f;
    s->spoke = (Rectangle) {s->center.x, s->center.y, s->spokeLength*0.2, s->spokeLength};
    s->spokeCenter = (Vector2) {s->spoke.width/2, s->spoke.height/2};
    return s;
}

void DrawSettingsIcon(Icon *i){
    SettingsIcon *s = i->data.settings;
    // Bounds
    DrawRectangleRec(s->bounds, RAYWHITE);
    // Spokes
    DrawRectanglePro(s->spoke, s->spokeCenter, s->spokeAngle, GRAY);
    DrawRectanglePro(s->spoke, s->spokeCenter, -s->spokeAngle, GRAY);
    DrawRectanglePro(s->spoke, s->spokeCenter, 0, GRAY);
    // Outer circle
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.4, GRAY);
    // Inner circle
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.2, RAYWHITE);
}
