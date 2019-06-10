#ifndef RANDOMWALKS_H
#define RANDOMWALKS_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include "paintingtool.h"


namespace Ui {
class RandomWalks;
}

class Widget; //forward declaration

class RandomWalks : public QDialog
{
    Q_OBJECT

public:
    explicit RandomWalks(QWidget *parent = nullptr);
    ~RandomWalks();

public slots:
    void on_backMain_clicked();

    void close();

signals:
    void sliderPressed();

private slots:
    void on_maxStepLengthSlider_sliderMoved(int position);

private:
    Ui::RandomWalks *ui;
    QTimer * timer;
    Widget *randomWalkWidget;
    PaintingTool randomWalkPainter;
    QLabel *maxStepSliderLabel;
    QSlider *maxStepSlider;


};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(PaintingTool *paintingtool, QWidget *parent);

public slots:
    void draw();


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    PaintingTool *paintingtool;
    int speedTimer;
};


#endif // RANDOMWALKS_H
