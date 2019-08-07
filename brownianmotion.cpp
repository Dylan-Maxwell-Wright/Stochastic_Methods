#include "brownianmotion.h"
#include "ui_brownianmotion.h"
#include "mainwindow.h"

BrownianMotion::BrownianMotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrownianMotion)
{
    ui->setupUi(this);
}

BrownianMotion::~BrownianMotion()
{
    delete ui;
}

void BrownianMotion::on_backMain_clicked()
{
    if(this->isVisible())
    {
        this->hide();
    }
}


