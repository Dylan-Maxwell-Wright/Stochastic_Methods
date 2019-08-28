#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <randomwalks.h>
#include <brownianmotion.h>
#include <demo.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void changeRandomWalks();

    void on_randomWalksButton_clicked();

    void on_brownianMotionPushButton_clicked();

    void changeBrownianMotion();

    void resetDemos();

private:
    Ui::MainWindow *ui;
    QTimer * timer;
    QTimer * demoTimer;
    RandomWalks *randomWalks;
    BrownianMotion *brownianMotion;
};

#endif // MAINWINDOW_H
