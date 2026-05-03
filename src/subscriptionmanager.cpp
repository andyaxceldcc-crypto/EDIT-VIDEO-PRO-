#include "subscriptionmanager.h"
#include <QSettings>
#include <QDebug>

SubscriptionManager::SubscriptionManager()
    : active(false)
{
    loadSubscriptionData();
}

bool SubscriptionManager::isSubscriptionActive() const
{
    if (!active) return false;
    
    return QDate::currentDate() <= expiryDate;
}

QDate SubscriptionManager::getSubscriptionExpiryDate() const
{
    return expiryDate;
}

void SubscriptionManager::activateSubscription(int durationDays)
{
    active = true;
    expiryDate = QDate::currentDate().addDays(durationDays);
    
    saveSubscriptionData();
    
    qDebug() << "Suscripción activada hasta:" << expiryDate.toString();
}

void SubscriptionManager::deactivateSubscription()
{
    active = false;
    expiryDate = QDate();
    
    saveSubscriptionData();
    
    qDebug() << "Suscripción desactivada";
}

int SubscriptionManager::daysRemainingInSubscription() const
{
    if (!isSubscriptionActive()) return 0;
    
    return QDate::currentDate().daysTo(expiryDate);
}

void SubscriptionManager::checkSubscriptionStatus()
{
    loadSubscriptionData();
    
    if (active && QDate::currentDate() > expiryDate) {
        qDebug() << "Suscripción expirada";
        deactivateSubscription();
    }
}

void SubscriptionManager::loadSubscriptionData()
{
    QSettings settings("FilmoraEditor", "FilmoraEditor");
    
    active = settings.value("subscription/active", false).toBool();
    expiryDate = settings.value("subscription/expiryDate", QDate()).toDate();
    userId = settings.value("subscription/userId", "").toString();
}

void SubscriptionManager::saveSubscriptionData()
{
    QSettings settings("FilmoraEditor", "FilmoraEditor");
    
    settings.setValue("subscription/active", active);
    settings.setValue("subscription/expiryDate", expiryDate);
    settings.setValue("subscription/userId", userId);
}
