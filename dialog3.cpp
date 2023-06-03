#include "dialog3.h"
#include "ui_dialog3.h"
#include "dialog2.h"
#include "Mainscene.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    setStyleSheet("background-color: rgb(196, 230, 255);");
    this->setWindowTitle(GAME_TITLE4);
    setWindowIcon(QIcon( GAME_ICON));
}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::on_pushButton_3_clicked()
{
    accept();
    Dialog2 *p = new Dialog2;
    p->show();
}
