#include "notification.h"
#include "globals.h"
#include "raylib.h"
#include <stdio.h>

void SetNotification(NotificationManager *notifMgr, Notification n){
    notifMgr->n = n;
    switch(n){
        case NOTIFY_INVALID_WORD:
        case NOTIFY_NOT_ENOUGH_LETTERS:
        {
            notifMgr->timer_s = 1.0f;
            notifMgr->fadeOut_s = 0.3f;
            notifMgr->rowShake_s = 0.25f;
        } break;
        case NOTIFY_NONE:
        {
            notifMgr->timer_s = 0.0f;
            notifMgr->fadeOut_s = 0.0f;
            notifMgr->rowShake_s = 0.0f;
        } break;
        default: break;
    }
}

void UpdateNotification(NotificationManager *notifMgr, float dt){
    if(notifMgr->timer_s > 0.0f){
        notifMgr->timer_s -= dt;
        notifMgr->rowShake_s -= dt;
        if(notifMgr->timer_s <= 0.0f){
            SetNotification(notifMgr, NOTIFY_NONE);
        }
    }
}

// Return 1 if notification is ongoing
int DrawNotifications(NotificationManager *notifMgr, GameState *g) {
    if (notifMgr->n == NOTIFY_NONE) return 0;

    const char *text = "";
    switch (notifMgr->n) {
        case NOTIFY_NOT_ENOUGH_LETTERS: text = "Not Enough Letters"; break;
        case NOTIFY_INVALID_WORD:     text = "Invalid Word"; break;
        default: return 0;
    }

    // Calculate Fading
    float alpha = 1.0f;
    if (notifMgr->timer_s < notifMgr->fadeOut_s) alpha = notifMgr->timer_s / notifMgr->fadeOut_s;

    // Centering Logic
    int textWidth = MeasureText(text, g->notifFontSize) + g->notifPadding * 2;
    Rectangle rec = {
        (GetScreenWidth() - textWidth) / 2,
        g->notifPosY,
        textWidth,
        g->notifFontSize * 2
    };

    DrawRectangleRec(rec, Fade(BLACK, alpha));
    DrawText(text, rec.x + g->notifPadding, rec.y + 10, g->notifFontSize, Fade(RAYWHITE, alpha));
    return 1;
}