#include "randomwalks.h"
#include "ui_randomwalks.h"
#include "mainwindow.h"

RandomWalks::RandomWalks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomWalks)
{
    ui->setupUi(this);
    Widget *randomWalkWidget = new Widget(&randomWalkPainter, this);
    timer = new QTimer();
}

RandomWalks::~RandomWalks()
{
    delete ui;
}

Widget::Widget(PaintingTool *randomWalkPainter, QWidget *parent)
    : QWidget(parent), paintingtool(randomWalkPainter)
{

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
