#include "paymentmanager.h"
#include <QUuid>
#include <QDebug>

PaymentManager::PaymentManager()
{
}

bool PaymentManager::processPayment(double amount)
{
    // Aquí se conectaría a un gateway de pago real como Stripe, PayPal, etc.
    
    if (chargeCard(amount)) {
        transactionId = QUuid::createUuid().toString();
        billingDate = QDate::currentDate().addMonths(1);
        
        qDebug() << "Pago procesado exitosamente";
        qDebug() << "Monto: $" << amount;
        qDebug() << "ID de transacción:" << transactionId;
        qDebug() << "Próxima facturación:" << billingDate.toString();
        
        return true;
    }
    
    return false;
}

bool PaymentManager::validateCardDetails(const QString &cardNumber, const QString &cvv)
{
    // Validar número de tarjeta (Luhn algorithm)
    if (cardNumber.length() < 13 || cardNumber.length() > 19) {
        return false;
    }
    
    // Validar CVV
    if (cvv.length() < 3 || cvv.length() > 4) {
        return false;
    }
    
    return true;
}

QString PaymentManager::getLastTransactionId() const
{
    return transactionId;
}

QDate PaymentManager::getNextBillingDate() const
{
    return billingDate;
}

bool PaymentManager::connectToPaymentGateway()
{
    // Aquí iría la lógica de conexión al gateway de pago
    return true;
}

bool PaymentManager::chargeCard(double amount)
{
    // Simulación de cargo
    if (connectToPaymentGateway()) {
        // En una aplicación real, aquí se haría la llamada a la API del gateway
        return true;
    }
    
    return false;
}
