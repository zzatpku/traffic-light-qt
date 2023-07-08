#ifndef SIMULATEWINDOW_H
#define SIMULATEWINDOW_H

#include <QWidget>
#include "map.h"
#include "car.h"
#include "config.h"
#include "light.h"
#include "picture.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SimulateWindow;
}

class SimulateWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulateWindow(QWidget *parent = nullptr);
    ~SimulateWindow();


    int update_speed;
    double car_stream_1;
    double car_stream_2;
    double car_stream_3;
    double car_stream_4;
    double light1; // 直行绿，左转红
    double light2; // 直行红，左转绿
    int judge_stop;//judge_stop为1代表正在运行，为0代表不在运行

    double evaluate_turn_right;
    double evaluate_turn_left;
    double evaluate_left_to_right;
    double evaluate_right_to_left;

    // 控制红绿灯的参数
    int light;//light=0表示可以直行，light=1表示可以左转, light=2表示黄灯
    int judge_yellow_light;

    int turn_right_flag;//是一个0到9的数
    int turn_left_flag;

    bool turning_right;
    bool turning_left;
    int turning_right_type;
    int turning_left_type;
    bool heading;

    bool play_again;

    void  initScene();
    QTimer m_Timer;
    double simulate_speed = 1;
//    double traffic_flow; // 车流量，模拟早晚高峰和平峰
    double msec; // 用于最后的统计界面
    int pass_car_number=0;
//    int rand_time=0; // 用于测试产生车辆的速度是否随模拟速度变化

    //启动游戏  用于启动定时器对象
    void playGame();
    void build_turn_right_Cars();
    void build_left_to_right_Cars();

    void build_turn_left_Cars();
    void build_right_to_left_Cars();
    //更新坐标
    void updateCarSpeedAndTimer();
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    void destruct_turn_right_cars();
    void destruct_turned_right_cars();
    void destruct_left_to_right_cars();
    void destruct_turn_left_cars();
    void destruct_turned_left_cars();
    void destruct_right_to_left_cars();
    //    void mouseMoveEvent(QMouseEvent *event);

    //地图对象
    Map m_map;

    QVector<Car> cars_turn_right;//准备右转的车
    QVector<Car> cars_turned_right;//右转完毕的车
    QVector<Car> cars_lef_to_right;//从左到右直行的车
    QVector<Car> cars_turn_left;//左转车辆
    QVector<Car> cars_turned_left;//左转完毕车辆
    QVector<Car> cars_right_to_left;//从右到左直行的车

    Car car_turning_right[9];//黄色正在右转的车
    Car car_turning_left[9];//黄色正在左转的车

    Car w_car_turning_right[9];
    Car w_car_turning_left[9];

    Car r_car_turning_right[9];
    Car r_car_turning_left[9];

    Car b_car_turning_right[9];
    Car b_car_turning_left[9];

    Car test;

    Light turn_left_red;
    Light turn_left_green;
    Light turn_left_yellow;
    Light left_to_right_red;
    Light left_to_right_green;
    Light left_to_right_yellow;
    Light right_to_left_red;
    Light right_to_left_green;
    Light right_to_left_yellow;

    QPixmap light_struct;

//    Picture con;
//    Picture sto;
//    Picture restart;
    void show_self();
    Ui::SimulateWindow *ui;

    double now_time;
    double car_jam_left_to_right;
    double car_jam_right_to_left;
    double car_jam_turn_right;
    double car_jam_turn_left;

    double jam_left_to_right;
    double jam_right_to_left;
    double jam_turn_right;
    double jam_turn_left;

    int turn_left_num;
    int turn_right_num;
    int left_to_right_num;
    int right_to_left_num;

};

#endif // SIMULATEWINDOW_H
