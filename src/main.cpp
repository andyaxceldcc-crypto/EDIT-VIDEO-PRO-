#include <QApplication>
#include "ui/main_window.h"
#include <QStyleFactory>
#include <QScreen>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set application properties
    app.setApplicationName("NUKE-PRO");
    app.setApplicationVersion("0.1.0");
    app.setStyle(QStyleFactory::create("Fusion"));

    // Create and show main window
    MainWindow window;
    window.show();

    return app.exec();
}
