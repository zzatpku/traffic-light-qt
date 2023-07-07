#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog3.h"
#include "mainscene.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);

    //初始化窗口大小
//    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    this->setWindowTitle(GAME_TITLE3);
//    setWindowIcon(QIcon( GAME_ICON));
//    setStyleSheet(GAME_ICON);
}

Dialog2::~Dialog2()
{
    delete ui;
}

//void Dialog2::on_pushButton_clicked()
//{
//    accept();
//    Dialog* w = new Dialog;
//    w->show();
//}

//void Dialog2::on_pushButton_help_clicked()
//{
//    accept();
//    Dialog3 *pp = new Dialog3;
//    pp->show();
//}
