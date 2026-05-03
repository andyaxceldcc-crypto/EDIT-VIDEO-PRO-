#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include <QString>
#include <QDate>

class SubscriptionManager
{
public:
    SubscriptionManager();
    
    bool isSubscriptionActive() const;
    QDate getSubscriptionExpiryDate() const;
    void activateSubscription(int durationDays = 30);
    void deactivateSubscription();
    int daysRemainingInSubscription() const;
    void checkSubscriptionStatus();
    
private:
    QString userId;
    QDate expiryDate;
    bool active;
    
    void loadSubscriptionData();
    void saveSubscriptionData();
};

#endif // SUBSCRIPTIONMANAGER_H
