#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QtWidgets>
#include "map.h"
#include "car.h"
#include "config.h"
#include <vector>
class MainScene : public QWidget
{
    Q_OBJECT

public:
    int car_stream_1;
    int light;//light=0表示可以直行，light=1表示可以左转, light=2表示黄灯
    int turn_right_flag;//是一个0到9的数
    int turn_left_flag;
    bool turning_right;
    bool turning_left;
    bool heading;
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void  initScene();
    QTimer m_Timer;
    //启动游戏  用于启动定时器对象
    void playGame();
    void build_turn_right_Cars();
    void build_left_to_right_Cars();

    void build_turn_left_Cars();
    void build_right_to_left_Cars();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    void destruct_turn_right_cars();
    void destruct_turned_right_cars();
    void destruct_left_to_right_cars();
    void destruct_turn_left_cars();
    void destruct_turned_left_cars();
    void destruct_right_to_left_cars();

    //地图对象
    Map m_map;

    QVector<Car> cars_turn_right;//准备右转的车
    QVector<Car> cars_turned_right;//右转完毕的车
    QVector<Car> cars_lef_to_right;//从左到右直行的车
    QVector<Car> cars_turn_left;//左转车辆
    QVector<Car> cars_turned_left;//左转完毕车辆
    QVector<Car> cars_right_to_left;//从右到左直行的车
    Car car_turning_right[9];
    Car car_turning_left[9];
};

#endif // MAINSCENE_H
