#include "endwindow.h"
#include "ui_endwindow.h"
#include "mainscene.h"

EndWindow::EndWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);
}

EndWindow::~EndWindow()
{
    delete ui;
}
