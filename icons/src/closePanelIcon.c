#include "closePanelIcon.h"
#include "icon.h"
#include <math.h>

ClosePanelIcon *MakeClosePanelIcon(Rectangle bounds){
    ClosePanelIcon *c = malloc(sizeof(ClosePanelIcon));
    c->bounds = bounds;
    c->center = (Vector2) {bounds.x + bounds.height/2, bounds.y + bounds.width/2};
    c->spokeLength = sqrt(pow(bounds.height, 2.0) + pow(bounds.width, 2.0))*0.6;
    c->spokeAngle = 45.0f;
    c->spoke = (Rectangle) {c->center.x, c->center.y, c->spokeLength*0.2, c->spokeLength};
    c->spokeCenter = (Vector2) {c->spoke.width/2, c->spoke.height/2};
    return c;
}

void DrawClosePanelIcon(Icon *i, GameState *g){
    (void) g;
    ClosePanelIcon *c = i->data.closePanel;
    // Bounds
    DrawRectangleRec(c->bounds, g->theme->closePanelBackground);
    // Spokes
    DrawRectanglePro(c->spoke, c->spokeCenter, c->spokeAngle, g->theme->closePanelSpokes);
    DrawRectanglePro(c->spoke, c->spokeCenter, -c->spokeAngle, g->theme->closePanelSpokes);
}

void ClickClosePanelIcon(GameState *g){
    g->gameScreen = GAMEPLAY;
}