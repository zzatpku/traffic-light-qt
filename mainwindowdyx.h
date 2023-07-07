#ifndef MAINWINDOWDYX_H
#define MAINWINDOWDYX_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include "dialog2.h"
#include "dialog3.h"
#include "mainscene.h"
#include "simulatewindow.h"
#include "endwindow.h"

namespace Ui {
class MainWindowDyx;
}

class MainWindowDyx : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDyx(QWidget *parent = nullptr);
    ~MainWindowDyx();

    Dialog* dialogSet = new Dialog;
    Dialog2* dialogStart = new Dialog2;
    Dialog3* dialogHelp = new Dialog3;
    EndWindow* windowEnd = new EndWindow;

    // 1:dialogStart 2:dialogSet 3:dialogHelp 4:dialogSet->windowSimulate
//    int central_widget;
    QTimer * Timer = new QTimer;
//    int counter;
    bool reset_timer = true;

private:
    Ui::MainWindowDyx *ui;
};

//int MainWindowDyx::counter = 1;

#endif // MAINWINDOWDYX_H
