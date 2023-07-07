#include "mainscene.h"
#include "ui_dialog.h"
#include "ui_simulatewindow.h"
#include "dialog2.h"
#include "config.h"
#include <QWidget>
#include <algorithm>
#include <random>
#include <QVector>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(GAME_TITLE2);
    setWindowIcon(QIcon( GAME_ICON));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnLogin_clicked()
{
    accept();
    bool ok = false;
    car_left_to_right = ui->txtleftstraight_->text().toInt(&ok,10);
    car_right_to_left = ui->txtrightstraight_->text().toInt(&ok,10);
    car_turn_left = ui->txtturnleft_->text().toInt(&ok,10);
    car_turn_right = ui->txtturnright_->text().toInt(&ok,10);
    light1 = ui->txtstraightgreen_->text().toInt(&ok, 10);
    light2 = ui->txtleftgreen_->text().toInt(&ok,10);
    double x1 = car_right_to_left;
    double x2 = car_left_to_right;
    double x3 = car_turn_left;
    double x4 = car_turn_right;
    double y1 = light1;
    double y2 = light2;

    windowSimulate->car_stream_1 = x1;
    windowSimulate->car_stream_2 = x4;
    windowSimulate->car_stream_3 = x2;
    windowSimulate->car_stream_4 = x3;
    windowSimulate->light1 = y1 * 1000;
    windowSimulate->light2 = y2 * 1000;
    this->hide();
//    windowSimulate->ui->dataBar->show();
    windowSimulate->show();
    windowSimulate->playGame();
}

