#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include "subscriptionmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Inicializar base de datos
    Database::getInstance().initializeDatabase();
    
    // Inicializar gerenciador de suscripciones
    SubscriptionManager subscriptionManager;
    subscriptionManager.checkSubscriptionStatus();
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
