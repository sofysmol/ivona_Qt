#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ivonaclient.h"

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
    IvonaClient* ivonaClient;
    QNetworkAccessManager* manager;
private slots:
 void handleButton();
 
};

#endif // MAINWINDOW_H
