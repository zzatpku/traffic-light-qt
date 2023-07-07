#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QtWidgets>
#include "map.h"
#include "car.h"
#include "config.h"
#include "light.h"
#include "picture.h"
#include "simulatewindow.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    SimulateWindow* windowSimulate = new SimulateWindow;
    int car_left_to_right;
    int car_right_to_left;
    int car_turn_left;
    int car_turn_right;
    int light1;
    int light2;
    Ui::Dialog *ui;
    void on_btnLogin_clicked();
signals:
    void showMain();
//private slots:
//    void on_btnLogin_clicked();

private:
};

#endif // MAINSCENE_H
