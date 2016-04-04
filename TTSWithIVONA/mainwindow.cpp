#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->speakButton, SIGNAL (clicked()), this, SLOT (handleButton()));
    QNetworkAccessManager* manager=new QNetworkAccessManager();
    ivonaClient=new IvonaClient(manager);
}
void MainWindow::handleButton()
{
    QString str=ui->textEdit->toPlainText();
    ivonaClient->getAudio(str,"en-GB");
}

MainWindow::~MainWindow()
{
    delete ui;
}
