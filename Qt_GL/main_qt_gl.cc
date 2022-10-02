#include <QApplication>
// #include "Constantes.h"
// #include "Vecteur3D.h"
// #include "Masse.h"
// #include "Systeme.h"
// #include "Integrateur.h"
// #include "IntegrateurEuler.h"
// #include "Liaison.h"
// #include "Tissu.h"
// #include "TissuChaine.h"
// #include "TissuRectangle.h"
// #include "TissuDisque.h"
// #include "TissuCompose.h"
// #include "Glwidget.h"
// #include "fenetre-commande.h"
#include "CommandWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    CommandWindow MainWindow(nullptr);
    MainWindow.show();

    return app.exec();
}
