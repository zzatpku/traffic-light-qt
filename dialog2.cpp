#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog3.h"
#include "Mainscene.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE3);
    setWindowIcon(QIcon( GAME_ICON));
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_clicked()
{
    accept();
    Dialog* w = new Dialog;
    w->show();
}

void Dialog2::on_pushButton_help_clicked()
{
    accept();
    Dialog3 *pp = new Dialog3;
    pp->show();
}
