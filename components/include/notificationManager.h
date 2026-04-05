#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include "gameState.h"

typedef enum Notification {
    NOTIFY_NONE,
    NOTIFY_NOT_ENOUGH_LETTERS,
    NOTIFY_INVALID_WORD,
    NOTIFY_HARDMODE_VIOLATION
} Notification;

typedef struct NotificationManager {
    Notification n;
    float timer_s; // Subtract detla time and change n when <= 0
    float fadeOut_s; // Time window for fading out notification
    float rowShake_s; // Time for row to shake
    char message[48]; // Buffer to store messages when applicable
} NotificationManager;

void SetNotification(NotificationManager *notifMgr, Notification n);

void UpdateNotification(NotificationManager *notifMgr, float dt);

int DrawNotifications(NotificationManager *notifMgr, GameState *g);

#endif // NOTIFICATION_MANAGER_H