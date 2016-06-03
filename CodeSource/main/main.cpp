#include "../GUI/mainwindow.h"
#include <QApplication>




int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // Creation de la fenetre principale
    MainWindow* principale = MainWindow::getInstance();
    principale->show();

    return app.exec();
}
