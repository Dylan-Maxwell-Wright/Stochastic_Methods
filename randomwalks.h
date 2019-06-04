#ifndef RANDOMWALKS_H
#define RANDOMWALKS_H

#include <QDialog>
#include <QTimer>


namespace Ui {
class RandomWalks;
}

class RandomWalks : public QDialog
{
    Q_OBJECT

public:
    explicit RandomWalks(QWidget *parent = nullptr);
    ~RandomWalks();

private slots:
    void on_backMain_clicked();

    void close();

private:
    Ui::RandomWalks *ui;
    QTimer * timer;

};

#endif // RANDOMWALKS_H
