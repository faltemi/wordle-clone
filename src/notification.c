#include "notification.h"
#include "raylib.h"
#include <stdio.h>

void SetNotification(NotificationManager *notifMgr, Notification n){
    notifMgr->n = n;
    switch(n){
        case NOTIFY_INVALID_WORD:
        case NOTIFY_NOT_ENOUGH_LETTERS:
        {
            notifMgr->lifespan_s = 2.0f;
            notifMgr->timer_s = 2.0f;
        } break;
        case NOTIFY_NONE:
        {
            notifMgr->lifespan_s = 0.0f;
            notifMgr->timer_s = 0.0f;
        } break;
        default: break;
    }
}

void UpdateNotification(NotificationManager *notifMgr, float dt){
    printf("DEBUG: UPDATE Notification %d\n", notifMgr->n);
    if(notifMgr->timer_s > 0.0f){
        notifMgr->timer_s -= dt;
        if(notifMgr->timer_s <= 0.0f){
            SetNotification(notifMgr, NOTIFY_NONE);
        }
    }
}

void DrawNotifications(NotificationManager *notifMgr) {
    if (notifMgr->n == NOTIFY_NONE) return;
    printf("DEBUG: DRAW Notification %d\n", notifMgr->n);
    const char *text = "";
    switch (notifMgr->n) {
        case NOTIFY_NOT_ENOUGH_LETTERS: text = "Not Enough Letters"; break;
        case NOTIFY_INVALID_WORD:     text = "Invalid Word"; break;
        default: return;
    }

    // Calculate Fading
    float alpha = 1.0f;
    if (notifMgr->timer_s < 0.5f) alpha = notifMgr->timer_s / 0.5f; // Fade out last 0.5s

    // Centering Logic
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    int pad = 20;
    Rectangle rec = {
        (GetScreenWidth() - (textWidth + pad*2)) / 2,
        60, // Y Position
        textWidth + pad * 2,
        40
    };

    DrawRectangleRec(rec, Fade(BLACK, alpha));
    DrawText(text, rec.x + pad, rec.y + 10, fontSize, Fade(RAYWHITE, alpha));
}