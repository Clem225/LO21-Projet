#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSignalMapper>
#include <QMainWindow>
#include <QWidget>
#include <QtXml>
#include "../XML/xml_dom.h"

namespace Ui
{
    class MainWindow;
}

// MainWindow est singleton. Permet également de simplifier l'envoi de signal
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
    MainWindow(const MainWindow& m){}
    /*! \brief Recopie (SINGLETON) */
    MainWindow& operator=(const MainWindow& m){}
    /*! \brief Destructeur (SINGLETON) */
    ~MainWindow();

    /*!
     * \class Handler
     * \brief Gestion du singleton (attribut publique, évite l'amitié)
    */
    struct Handler {
    MainWindow* instance;
    Handler():instance(nullptr){}
    ~Handler(){delete instance;} // Le destructeur libere la memoire de li'nstance unique
    };

    static Handler handler;

    Xml_Dom paramXML;

public slots:
    // Raffraichit l'affichage de la pile
    void refreshPile();
    // Envoi la commande de la ligne de commande en execution
    void sendCMD();
    // Clavier cliquable
    void addCMD(QString cmd);
    // Message utilisateur
    void setMsg(QString msg);
    // Affiche la fenetre de parametre
    void param();
    void atomes();
    void programmes();
    // Affiche ou non le clavier
    void showKeyboard();
    // Fait un bip si active
    void doBip();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
