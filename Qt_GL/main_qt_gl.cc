#include <QApplication>
// #include "Constantes.h"
// #include "Glwidget.h"
// #include "CommandWindow.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    // CommandWindow mainWindow(nullptr);
    MainWindow mainWindow(nullptr);
    mainWindow.show();

    return app.exec();
}
