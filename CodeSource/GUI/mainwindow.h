#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSignalMapper>
#include <QMainWindow>
#include <QWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // Signal mapper
    QSignalMapper *signalMapper;

public slots:
    void refresh();
    void sendCMD();
    void addCMD(QString cmd);
};

#endif // MAINWINDOW_H
