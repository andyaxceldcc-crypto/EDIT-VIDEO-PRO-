#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include <QString>
#include <QDate>

class PaymentManager
{
public:
    PaymentManager();
    
    bool processPayment(double amount);
    bool validateCardDetails(const QString &cardNumber, const QString &cvv);
    QString getLastTransactionId() const;
    QDate getNextBillingDate() const;
    
private:
    QString transactionId;
    QDate billingDate;
    
    bool connectToPaymentGateway();
    bool chargeCard(double amount);
};

#endif // PAYMENTMANAGER_H
