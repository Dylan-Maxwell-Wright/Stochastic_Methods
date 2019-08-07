#ifndef BROWNIANMOTION_H
#define BROWNIANMOTION_H

#include <QDialog>

namespace Ui {
class BrownianMotion;
}

class BrownianMotion : public QDialog
{
    Q_OBJECT

public:
    explicit BrownianMotion(QWidget *parent = nullptr);
    ~BrownianMotion();

private slots:
    void on_backMain_clicked();

private:
    Ui::BrownianMotion *ui;
};

#endif // BROWNIANMOTION_H
