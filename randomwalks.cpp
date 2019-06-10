#include "randomwalks.h"
#include "ui_randomwalks.h"
#include "mainwindow.h"
#include "QPainter"
#include "QSlider"
#include "QLineEdit"

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

void Widget::draw()
{

}

void Widget::paintEvent(QPaintEvent *event)
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



void RandomWalks::on_maxStepLengthSlider_sliderMoved(int position)
{
    ui->maxStepSliderLabel->setNum(position);
}
