#include "randomwalks.h"
#include "ui_randomwalks.h"
#include "mainwindow.h"

MainWindow *mainWindow;

RandomWalks::RandomWalks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomWalks)
{
    ui->setupUi(this);

    timer = new QTimer();
}

RandomWalks::~RandomWalks()
{
    delete ui;
}



void RandomWalks::on_backMain_clicked()
{
    close();
}

void RandomWalks::close()
{
    if(this->isVisible())
    {
        this->hide();
    }
}
