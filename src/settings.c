#include "settings.h"
#include <math.h>

void InitSettingsIcon(SettingsIcon *s, Rectangle bounds){
    s->bounds = bounds;
    s->center = (Vector2) {bounds.x + bounds.height/2, bounds.y + bounds.width/2};
    s->spokeLength = sqrt(pow(bounds.height, 2.0) + pow(bounds.width, 2.0))*0.6;
    s->spokeAngle = 60.0f;
    s->spoke = (Rectangle) {s->center.x, s->center.y, s->spokeLength*0.2, s->spokeLength};
    s->spokeCenter = (Vector2) {s->spoke.width/2, s->spoke.height/2};
}

void DrawSettingsIcon(SettingsIcon *s){
    // Bounds
    DrawRectangleRec(s->bounds, BLACK);
    // Spokes
    DrawRectanglePro(s->spoke, s->spokeCenter, s->spokeAngle, GRAY);
    DrawRectanglePro(s->spoke, s->spokeCenter, -s->spokeAngle, GRAY);
    DrawRectanglePro(s->spoke, s->spokeCenter, 0, GRAY);
    // Outer circle
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.4, GRAY);
    // Inner circle
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.2, BLACK);
}

void DrawSettingsScreen(){
    DrawRectangleRec((Rectangle){0, 0, 100, 100}, BLACK);
}