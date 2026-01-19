#ifndef NOTIFICATION_H
#define NOTIFICATION_H

typedef enum Notification {
    NOTIFY_NONE,
    NOTIFY_NOT_ENOUGH_LETTERS,
    NOTIFY_INVALID_WORD
} Notification;

typedef struct NotificationManager {
    Notification n;
    float timer_s; // Subtract detla time and change n when <= 0
    float fadeOut_s; // Time window for fading out notification
    float rowShake_s; // Time for row to shake
} NotificationManager;

void SetNotification(NotificationManager *notifMgr, Notification n);

void UpdateNotification(NotificationManager *notifMgr, float dt);

int DrawNotifications(NotificationManager *notifMgr);

#endif // NOTIFICATION_H