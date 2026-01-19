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
    // Outer box
    // Rectangle outerRec = {0, 0, 50, 50};
    // Vector2 outerRecCenter = {outerRec.x + outerRec.height/2, outerRec.y + outerRec.width/2};
    // float recLen = sqrt(pow(outerRec.height, 2.0) + pow(outerRec.width, 2.0))*0.6;
    
    DrawRectangleRec(s->bounds, BLACK);
    // 3 rectangles
    // Rectangle recLeft = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    // Vector2 origin = {recLeft.width / 2, recLeft.height / 2 };
    // float angle = 60.0f;
    DrawRectanglePro(s->spoke, s->spokeCenter, s->spokeAngle, GRAY);

    // Rectangle recRight = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    // Vector2 origin2 = {recRight.width / 2, recRight.height / 2 };
    // float angle2 = -60.0f;
    DrawRectanglePro(s->spoke, s->spokeCenter, -s->spokeAngle, GRAY);

    // Rectangle rec3 = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    // Vector2 origin3 = {rec3.width / 2, rec3.height / 2 };
    // float angle3 = 0.0f;
    DrawRectanglePro(s->spoke, s->spokeCenter, 0, GRAY);
    // outer circle
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.4, GRAY);
    // inner circle: color of background
    DrawCircle((int)s->center.x, (int)s->center.y, s->spokeLength*0.2, BLACK);

}