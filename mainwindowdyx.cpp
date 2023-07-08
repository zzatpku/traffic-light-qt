#include "mainwindowdyx.h"
#include "dialog2.h"
#include "dialog3.h"
#include "mainscene.h"
#include "ui_mainwindowdyx.h"
#include "ui_dialog2.h"
#include "ui_dialog.h"
#include "ui_dialog3.h"
#include "ui_simulatewindow.h"
#include "ui_endwindow.h"
#include "simulatewindow.h"

#include <QDebug>
// #include <QDialog>
#include <QPushButton>
#include <QTimer>

//int MainWindowDyx::counter

MainWindowDyx::MainWindowDyx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowDyx)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon( GAME_ICON));
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    ui->toolBar->hide();
    this->setCentralWidget(dialogStart);
    //    central_widget=1;
    
    
    // 所有的信号和槽
    //0.计时器与计数器
    connect(Timer,&QTimer::timeout,[=]()
    {
        static double counter=0;
        if(reset_timer==true)
        {
            reset_timer=false;
            counter=0;
        }
        double simulate_speed = dialogSet->windowSimulate->simulate_speed;
        // counter是static类型，一直累加，代表总启动时长，因此用全局变量msec来存放这一次定时器的启动时长
        dialogSet->windowSimulate->msec=counter;

//        dialogSet->windowSimulate->m_Timer.setInterval(int(GAME_RATE*simulate_speed));
        // 道路左侧，显示交通拥堵程度
                if(dialogSet->windowSimulate->jam_right_to_left<=0.5)
                {
                    int r = int(510 * dialogSet->windowSimulate->jam_right_to_left);
                    int g = 255;
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamToLeft->
                            setStyleSheet(stylesheet);
                }
                else
                {
                    int r = 255;
                    int g = int(255 - 510 * (dialogSet->windowSimulate->jam_right_to_left - 0.5));
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamToLeft->
                            setStyleSheet(stylesheet);
                }

                if(dialogSet->windowSimulate->jam_left_to_right<=0.5)
                {
                    int r = int(510 * dialogSet->windowSimulate->jam_left_to_right);
                    int g = 255;
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamToRight->
                            setStyleSheet(stylesheet);
                }
                else
                {
                    int r = 255;
                    int g = int(255 - 510 * (dialogSet->windowSimulate->jam_left_to_right - 0.5));
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamToRight->
                            setStyleSheet(stylesheet);
                }

                if(dialogSet->windowSimulate->jam_turn_left<=0.5)
                {
                    int r = int(510 * dialogSet->windowSimulate->jam_turn_left);
                    int g = 255;
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamTurnLeft->
                            setStyleSheet(stylesheet);
                }
                else
                {
                    int r = 255;
                    int g = int(255 - 510 * (dialogSet->windowSimulate->jam_turn_left - 0.5));
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamTurnLeft->
                            setStyleSheet(stylesheet);
                }

                if(dialogSet->windowSimulate->jam_turn_right<=0.5)
                {
                    int r = int(510 * dialogSet->windowSimulate->jam_turn_right);
                    int g = 255;
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamTurnRight->
                            setStyleSheet(stylesheet);
                }
                else
                {
                    int r = 255;
                    int g = int(255 - 510 * (dialogSet->windowSimulate->jam_turn_right - 0.5));
                    int b = 0;
                    QString stylesheet = QString("background-color: rgba(%1, %2, %3, 0.7);").
                            arg(QString::number(r), QString::number(g), QString::number(b));
                    dialogSet->windowSimulate->ui->colorJamTurnRight->
                            setStyleSheet(stylesheet);
                }


        dialogSet->windowSimulate->ui->lableJamLeftToRight->
                setText(QString::number(dialogSet->windowSimulate->jam_left_to_right,'f', 4));
        dialogSet->windowSimulate->ui->lableJamRightToLeft->
                setText(QString::number(dialogSet->windowSimulate->jam_right_to_left,'f', 4));
        dialogSet->windowSimulate->ui->lableJamTurnLeft->
                setText(QString::number(dialogSet->windowSimulate->jam_turn_left,'f', 4));
        dialogSet->windowSimulate->ui->lableJamTurnRight->
                setText(QString::number(dialogSet->windowSimulate->jam_turn_right,'f', 4));

        dialogSet->windowSimulate->ui->lableShowSimulateRate->
                setText(QString("×")+QString::number(simulate_speed,'f',1));
        //100ms发出一次信号，所以+=0.1*。。。
        dialogSet->windowSimulate->ui->lableShowTime->
                setText(QString::number(counter+=0.1*simulate_speed,'f',1));
        dialogSet->windowSimulate->ui->lableShowPassCar->
                setText(QString::number(this->dialogSet->windowSimulate->pass_car_number));

        //dialogSet->windowSimulate->updateCarSpeedAndTimer();
    });
    //1.mainwindowdyx**********************************************************
//    connect(ui->actionHeavyFlow,&QAction::triggered,[=]()
//    {
//        dialogSet->windowSimulate->traffic_flow=700;
//    });
//    connect(ui->actionNormalFlow,&QAction::triggered,[=]()
//    {
//        dialogSet->windowSimulate->traffic_flow=1000;
//    });
//    connect(ui->actionLightFlow,&QAction::triggered,[=]()
//    {
//        dialogSet->windowSimulate->traffic_flow=1300;
//    });

    connect(ui->actionNew,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->judge_stop=0;
        Timer->stop();
        int ans = QMessageBox::question(this, tr("Warning"), tr("是否结束模拟并返回主界面？"));
        if(ans==QMessageBox::Yes)
        {
            Timer->stop();
            delete dialogSet->windowSimulate;

            ui->toolBar->hide();

            this->takeCentralWidget();
            this->setCentralWidget(dialogStart);
            //            central_widget=1;

            dialogStart->show();
        }
        else
        {
            dialogSet->windowSimulate->judge_stop=1;
            Timer->start();
        }
    });

    connect(ui->actionChangeParameter,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->judge_stop=0;
        Timer->stop();
        int ans = QMessageBox::question(this, tr("Warning"), tr("是否结束模拟并修改参数？"));
        if(ans==QMessageBox::Yes)
        {
            Timer->stop();
            delete dialogSet->windowSimulate;

            ui->toolBar->hide();

            this->takeCentralWidget();
            this->setCentralWidget(dialogSet);
            //            central_widget=2;

            dialogSet->show();
        }
        else
        {
            dialogSet->windowSimulate->judge_stop=1;
            Timer->start();
        }
    });

    connect(ui->actionStopSimulate,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->judge_stop=0;
        Timer->stop();
    });
    connect(ui->actionContinueSimulate,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->judge_stop=1;
        Timer->start();
    });
    
    // 展示统计数据页面
    connect(ui->actionEndSimulate,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->judge_stop=0;
        Timer->stop();
        int ans = QMessageBox::question(this, tr("Warning"), tr("是否结束模拟？"));
        if(ans==QMessageBox::Yes)
        {
            delete dialogSet->windowSimulate;
            ui->toolBar->hide();

            this->takeCentralWidget();
            this->setCentralWidget(windowEnd);
            int pass_car_number=dialogSet->windowSimulate->pass_car_number;
            double msec=dialogSet->windowSimulate->msec;
            windowEnd->ui->lableShowPassCar->setText(QString::number(pass_car_number));
            windowEnd->ui->lableShowTime->setText(QString::number(msec));

            double tmp;
            tmp = dialogSet->windowSimulate->jam_left_to_right * dialogSet->windowSimulate->jam_left_to_right + dialogSet->windowSimulate->jam_right_to_left * dialogSet->windowSimulate->jam_right_to_left
                     + dialogSet->windowSimulate->jam_turn_left * dialogSet->windowSimulate->jam_turn_left + dialogSet->windowSimulate->jam_turn_right * dialogSet->windowSimulate->jam_turn_right
                    - (dialogSet->windowSimulate->jam_left_to_right + dialogSet->windowSimulate->jam_right_to_left + dialogSet->windowSimulate->jam_turn_left + dialogSet->windowSimulate->jam_turn_right) *
                    (dialogSet->windowSimulate->jam_left_to_right + dialogSet->windowSimulate->jam_right_to_left + dialogSet->windowSimulate->jam_turn_left + dialogSet->windowSimulate->jam_turn_right) / 4;
            char evaluation;
            if(tmp < 0.04) evaluation = 'S';
            else if(tmp < 0.1) evaluation = 'A';
            else if(tmp < 0.25) evaluation = 'B';
            else if(tmp < 0.6) evaluation = 'C';
            else evaluation = 'D';
            windowEnd->ui->lableParameterEvaluation->setText(QString(evaluation));

            windowEnd->show();

        }
        else
        {
            dialogSet->windowSimulate->judge_stop=1;
            Timer->start();
        }
    });

    // 调整倍速
    connect(ui->action_1Speed,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->simulate_speed=1;
    });
    connect(ui->action_2Speed,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->simulate_speed=2;
    });
    connect(ui->action_4Speed,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->simulate_speed=4;
    });
    connect(ui->action_16Speed,&QAction::triggered,[=]()
    {
        dialogSet->windowSimulate->simulate_speed=16;
    });
    
    
    
    //2.dialogStart**********************************************************
    connect(dialogStart->ui->pushButton,&QPushButton::clicked,[=]()
    {
        this->takeCentralWidget();
        this->setCentralWidget(dialogSet);
        //        central_widget=2;
        
        dialogSet->show();
    });
    connect(dialogStart->ui->pushButton_help,&QPushButton::clicked,[=]()
    {
        this->takeCentralWidget();
        this->setCentralWidget(dialogHelp);
        //        central_widget=3;
        static QMovie movie(":res/baymax.gif");
        movie.start();
        dialogHelp->ui->label->setMovie(&movie);
        //ui->label->show();
        this->show();
        dialogHelp->show();
    });
    connect(dialogStart->ui->pushButton_exit,&QPushButton::clicked,this,&QMainWindow::close);
    
    //3.dialogSet**********************************************************
    connect(dialogSet->ui->btnLogin_ ,&QPushButton::clicked,[=]()
    {
        if(dialogSet->ui->txtstraightgreen_->text()!=""&&
                dialogSet->ui->txtleftgreen_->text()!=""&&
                dialogSet->ui->txtrightstraight_->text()!=""&&
                dialogSet->ui->txtleftstraight_->text()!=""&&
                dialogSet->ui->txtturnright_->text()!=""&&
                dialogSet->ui->txtturnleft_->text()!="")
        {
            // 开启工具栏
            ui->toolBar->show();
            
            // 定时器
            reset_timer=true;
            Timer->start(100);
            
            
            // 设置中心窗口
            this->takeCentralWidget();
            dialogSet->windowSimulate = new SimulateWindow;
            dialogSet->windowSimulate->ui->lableShowTime->setText(QString::number(0));
            dialogSet->windowSimulate->ui->lableShowPassCar->setText(QString::number(0));
            this->setCentralWidget(dialogSet->windowSimulate);
            //            central_widget=4;
            
            dialogSet->on_btnLogin_clicked();
            
            
            
            //            // 计时器每秒发一次信号
            //            dialogSet->windowSimulate->timer_simulate->start(1000);
            //            qDebug()<<"press button"<<endl;
            //            if(dialogSet->windowSimulate->timer_simulate->isActive())
            //            {
            //                dialogSet->windowSimulate->hide();
            //            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"), tr("Haven't input all numbers yet!"), QMessageBox::Yes);
        }
    });
    
    //4.dialogHelp**********************************************************
    connect(dialogHelp->ui->pushButton_3 ,&QPushButton::clicked,[=]()
    {
        this->takeCentralWidget();
        this->setCentralWidget(dialogStart);
        //        central_widget=1;
        
        dialogStart->show();
    });

    //5.windowEnd**********************************************************
    connect(windowEnd->ui->pushButtonBackMainWindow,&QPushButton::clicked,[=]()
    {
        this->takeCentralWidget();
        this->setCentralWidget(dialogStart);
        //        central_widget=1;

        dialogStart->show();
    });
    connect(windowEnd->ui->pushButtonExit,&QPushButton::clicked,this,&QMainWindow::close);
}

MainWindowDyx::~MainWindowDyx()
{
    delete ui;
    //    delete dialogSet;
    //    delete dialogStart;
    //    delete dialogHelp;
}
