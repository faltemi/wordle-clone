#include "settings.h"
#include "raylib.h"
#include <math.h>

void DrawSettings(){
    // Outer box
    Rectangle outerRec = {0, 0, 50, 50};
    DrawRectangleRec(outerRec, BLACK);
    Vector2 outerRecCenter = {outerRec.x + outerRec.height/2, outerRec.y + outerRec.width/2};
    float recLen = sqrt(pow(outerRec.height, 2.0) + pow(outerRec.width, 2.0))*0.6;

    // 3 rectangles
    Rectangle recLeft = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    Vector2 origin = {recLeft.width / 2, recLeft.height / 2 };
    float angle = 60.0f;
    DrawRectanglePro(recLeft, origin, angle, GRAY);

    Rectangle recRight = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    Vector2 origin2 = {recRight.width / 2, recRight.height / 2 };
    float angle2 = -60.0f;
    DrawRectanglePro(recRight, origin2, angle2, GRAY);

    Rectangle rec3 = {outerRecCenter.x, outerRecCenter.y, 10, recLen};
    Vector2 origin3 = {rec3.width / 2, rec3.height / 2 };
    float angle3 = 0.0f;
    DrawRectanglePro(rec3, origin3, angle3, GRAY);
    // outer circle
    DrawCircle((int)outerRecCenter.x, (int)outerRecCenter.y, recLen*0.4, GRAY);
    // inner circle: color of background
    DrawCircle((int)outerRecCenter.x, (int)outerRecCenter.y, recLen*0.2, BLACK);

}