#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSignalMapper>
#include <QMainWindow>
#include <QWidget>
#include <QtXml>
#include "../XML/xml_dom.h"

/*!
 * \file mainwindow.h
 * \brief Fenetre principale
 * \author Blanquet - Martinache
 * \version 0.1
 */

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*! \brief (SINGLETON) */
    static MainWindow *getInstance();
    /*! \brief (SINGLETON) */
    static void libererInstance();

private:
    // Qt Designer
    Ui::MainWindow *ui;
    // Signal mapper
    QSignalMapper *signalMapper;

    /*! \brief Constructeur (SINGLETON) */
    explicit MainWindow(QWidget *parent = 0);
    /*! \brief Constructeur (SINGLETON) */
    MainWindow(const MainWindow& m);
    /*! \brief Recopie (SINGLETON) */
    MainWindow& operator=(const MainWindow& m);
    /*! \brief Destructeur (SINGLETON) */
    ~MainWindow();

    /*!
     * \class Handler
     * \brief Gestion du singleton (attribut publique, évite l'amitié)
    */
    struct Handler {
    MainWindow* instance;
    Handler():instance(nullptr){}
    ~Handler(){delete instance;}
    };

    static Handler handler;

    Xml_Dom paramXML;

public slots:
    /*! \brief Raffraichit l'affichage de la pile */
    void refreshPile();
    /*! \brief Envoi au controlleur la commande ecrite sur le GUI */
    void sendCMD();
    /*! \brief Ajoute un QString a la liste de commande (utilisé pour le clavier cliquable) */
    void addCMD(QString cmd);
    /*! \brief Affiche un message a l'utilisateur*/
    void setMsg(QString msg);
    /*! \brief Affiche la fenetre Parametre */
    void param();
    /*! \brief Affiche la fenetre atomes */
    void atomes();
    /*! \brief Affiche la fenetre programme */
    void programmes();
    /*! \brief Affiche le clavier selon la valeur du XML */
    void showKeyboard();
    /*! \brief Fait un BIP si c'est activé */
    void doBip();
    /*! \brief Routine de fermeture */
    void closeEvent(QCloseEvent *event);

    /*! \brief Envoi UNDO au controleur */
    void undo();
    /*! \brief Envoi REDO au controleur */
    void redo();
};

#endif // MAINWINDOW_H
