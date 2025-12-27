#ifndef NOTIFICATION_H
#define NOTIFICATION_H

typedef enum Notification {
    NONE,
    NOT_ENOUGH_LETTERS,
    INVALID_WORD
} Notification;

typedef struct NotificationManager {
    Notification n;
    int timer; // Subtract detla time and change n when <= 0
    int lifespan; // If fadeout
} NotificationManager;

#endif // NOTIFICATION_H