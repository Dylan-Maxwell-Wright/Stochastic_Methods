#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <randomwalks.h>

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

private:
    Ui::MainWindow *ui;
    QTimer * timer;
    RandomWalks *randomWalks;
};

#endif // MAINWINDOW_H
