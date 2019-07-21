#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QBrush tb(Qt::transparent);
    ui->randomWalksButton->setPalette(QColor(0, 0, 0, 0));


    timer = new QTimer();
    randomWalks = new RandomWalks();
    randomWalks->setModal(true);
    connect(timer, &QTimer::timeout, this, &MainWindow::changeRandomWalks);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeRandomWalks()
{
    if(randomWalks->isVisible())
    {

    }
    else
    {
        randomWalks->show();
    }
}

void MainWindow::on_randomWalksButton_clicked()
{
    changeRandomWalks();
}


