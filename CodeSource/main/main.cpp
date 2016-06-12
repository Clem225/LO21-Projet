#include "../GUI/mainwindow.h"
#include <QApplication>


/*!
 * \file main.cpp
 * \brief MAIN
 * \author Blanquet - Martinache
 * \version 0.1
 */

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // Creation de la fenetre principale
    MainWindow* principale = MainWindow::getInstance();
    principale->show();

    return app.exec();
}
