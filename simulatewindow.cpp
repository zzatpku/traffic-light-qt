#include "simulatewindow.h"
#include "ui_simulatewindow.h"

#include "mainscene.h"
#include "ui_dialog.h"
//#include "ui_mainscene.h"
#include "dialog2.h"
#include "config.h"
#include <QWidget>
#include <algorithm>
#include <random>
#include <QVector>

SimulateWindow::SimulateWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulateWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);

    initScene();
    car_stream_1 = 1;
    car_stream_2 = 1;
    car_stream_3 = 1;
    car_stream_4 = 1;
    light = 0;
#define fuck(id, id0) \
    car_turning_right[id] = Car(CAR_TURN_ ## id0); \
    car_turning_right[id].setPosition(TURN_RIGHT_ ## id0 ## _X, TURN_RIGHT_ ## id0 ## _Y);\
    w_car_turning_right[id] = Car(W_CAR_TURN_ ## id0); \
    w_car_turning_right[id].setPosition(TURN_RIGHT_ ## id0 ## _X, TURN_RIGHT_ ## id0 ## _Y);\
    r_car_turning_right[id] = Car(R_CAR_TURN_ ## id0); \
    r_car_turning_right[id].setPosition(TURN_RIGHT_ ## id0 ## _X, TURN_RIGHT_ ## id0 ## _Y);\
    b_car_turning_right[id] = Car(B_CAR_TURN_ ## id0); \
    b_car_turning_right[id].setPosition(TURN_RIGHT_ ## id0 ## _X, TURN_RIGHT_ ## id0 ## _Y);\
    car_turning_left[id] = Car(CAR_TURN_0 ## id0); \
    car_turning_left[id].setPosition(TURN_LEFT_ ## id0 ## _X, TURN_LEFT_ ## id0 ## _Y);\
    w_car_turning_left[id] = Car(W_CAR_TURN_0 ## id0); \
    w_car_turning_left[id].setPosition(TURN_LEFT_ ## id0 ## _X, TURN_LEFT_ ## id0 ## _Y);\
    r_car_turning_left[id] = Car(R_CAR_TURN_0 ## id0); \
    r_car_turning_left[id].setPosition(TURN_LEFT_ ## id0 ## _X, TURN_LEFT_ ## id0 ## _Y);\
    b_car_turning_left[id] = Car(B_CAR_TURN_0 ## id0); \
    b_car_turning_left[id].setPosition(TURN_LEFT_ ## id0 ## _X, TURN_LEFT_ ## id0 ## _Y)

    fuck(0, 10);
    fuck(1, 20);
    fuck(2, 30);
    fuck(3, 40);
    fuck(4, 50);
    fuck(5, 60);
    fuck(6, 70);
    fuck(7, 80);
    fuck(8, 90);
    //----------------------------------------------------------------------
    turn_left_red = Light(RED_LIGHT);
    turn_left_red.setPosition(780, 5);
    turn_left_green = Light(GREEN_LIGHT);
    turn_left_green.setPosition(780, 5);
    turn_left_yellow = Light(YELLOW_LIGHT);
    turn_left_yellow.setPosition(780, 5);

    left_to_right_red = Light(RED_LIGHT);
    left_to_right_red.setPosition(1060, 125);
    left_to_right_green = Light(GREEN_LIGHT);
    left_to_right_green.setPosition(1060, 125);
    left_to_right_yellow = Light(YELLOW_LIGHT);
    left_to_right_yellow.setPosition(1060, 125);

    right_to_left_red = Light(RED_LIGHT);
    right_to_left_red.setPosition(600, 125);
    right_to_left_green = Light(GREEN_LIGHT);
    right_to_left_green.setPosition(600, 125);
    right_to_left_yellow = Light(YELLOW_LIGHT);
    right_to_left_yellow.setPosition(600, 125);

    evaluate_turn_right = 1;
    evaluate_turn_left = 1;
    evaluate_left_to_right = 1;
    evaluate_right_to_left = 1;

    now_time = 0;
    car_jam_left_to_right = 0;
    car_jam_right_to_left = 0;
    car_jam_turn_right = 0;
    car_jam_turn_left = 0;

    jam_left_to_right = 0;
    jam_right_to_left = 0;
    jam_turn_right = 0;
    jam_turn_left = 0;

    light_struct.load(TRAFFIC_LIGHT_1);

    turn_right_flag = 0;
    turn_left_flag = 0;
    turning_right = false;
    turning_left = false;
    heading = false;
    update_speed = 1;
    judge_stop = 1;
    play_again = false;

    turn_left_num = 0;
    turn_right_num = 0;
    left_to_right_num = 0;
    right_to_left_num = 0;

    test = Car(CAR_PATH);

}

SimulateWindow::~SimulateWindow()
{
    delete ui;
}



void SimulateWindow::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //设置图标资源
    setWindowIcon(QIcon(GAME_ICON));
    setAttribute(Qt::WA_DeleteOnClose);
    //定时器设置
    m_Timer.setInterval(GAME_RATE);
}
void SimulateWindow::destruct_turn_right_cars(){
    for(int i = 1; i < cars_turn_right.count(); i++)
    {
        cars_turn_right[i].number--;
    }
    cars_turn_right.pop_front();
}
void SimulateWindow::destruct_turned_right_cars(){
    for(int i = 1; i < cars_turned_right.count(); i++)
    {
        cars_turned_right[i].number--;
    }
    cars_turned_right.pop_front();
    pass_car_number++;
}
void SimulateWindow::destruct_left_to_right_cars(){
    for(int i = 1; i < cars_lef_to_right.count(); i++)
    {
        cars_lef_to_right[i].number--;
    }
    cars_lef_to_right.pop_front();
    pass_car_number++;
}
void SimulateWindow::destruct_right_to_left_cars(){
    for(int i = 1; i < cars_right_to_left.count(); i++)
    {
        cars_right_to_left[i].number--;
    }
    cars_right_to_left.pop_front();
    pass_car_number++;
}
void SimulateWindow::destruct_turn_left_cars(){
    for(int i = 1; i < cars_turn_left.count(); i++)
    {
        cars_turn_left[i].number--;
    }
    cars_turn_left.pop_front();
}
void SimulateWindow::destruct_turned_left_cars(){
    for(int i = 1; i < cars_turned_left.count(); i++)
    {
        cars_turned_left[i].number--;
    }
    cars_turned_left.pop_front();
    pass_car_number++;
}
void SimulateWindow::playGame()
{
    //启动定时器
    m_Timer.start();
    //定时器设置
    m_Timer.setInterval(GAME_RATE);

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        if(judge_stop)
        {
            m_Timer.setInterval(GAME_RATE / simulate_speed);
            // ***************************************红绿灯事件***************************************
            int t = int(msec * 1000);
            //第一种情况：调整定时器的频率
            // 直行绿light1，左转绿light2，两个黄灯情况各2s
            t = t % int((light1 + light2 + 4000));
            if(t <= light1) light = 0;
            else if((light1 + 2000) <= t && t <= (light1 + light2 + 2000)) light = 1;
            else
            {
                light = 2;
                if(t < (light1 + 2000)) judge_yellow_light = false;
                else judge_yellow_light = true;
            }

            // ***************************************生成汽车事件***************************************
            int parameter = 6000;
            int ran = rand() % (parameter);
            if(ran < 2 * car_stream_1)
                build_left_to_right_Cars();
            ran = rand() % (parameter);
            if(ran < 2 * car_stream_2)
                build_turn_right_Cars();
            ran = rand() % (parameter);
            if(ran < 2 * car_stream_3)
                build_right_to_left_Cars();
            ran = rand() % (parameter);
            if(ran < 2 * car_stream_4)
                build_turn_left_Cars();
            if(left_to_right_num){
                build_left_to_right_Cars();
                left_to_right_num--;
            }
            if(right_to_left_num){
                build_right_to_left_Cars();
                right_to_left_num--;
            }
            if(turn_right_num){
                build_turn_right_Cars();
                turn_right_num--;
            }
            if(turn_left_num){
                build_turn_left_Cars();
                turn_left_num--;
            }
            int num1 = 0;
            int num2 = 0;
            for(int i = 0; i < cars_lef_to_right.size(); i++) if(cars_lef_to_right[i].m_X <= 410) num1++;
            for(int i = 0; i < cars_right_to_left.size(); i++) if(cars_right_to_left[i].m_X >= 970) num2++;
            if(num1 + left_to_right_num >= 6) car_jam_left_to_right++;
            if(num2 + right_to_left_num >= 6) car_jam_right_to_left++;
            if(cars_turn_left.size() + turn_left_num >= 5) car_jam_turn_left += 0.6;
            if(cars_turn_left.size() + turn_left_num >= 6) car_jam_turn_left += 0.4;
            if(cars_turn_right.size() + turn_right_num >= 5) car_jam_turn_right += 0.6;
            if(cars_turn_right.size() + turn_right_num >= 6) car_jam_turn_right += 0.4;
            now_time++;
            jam_left_to_right = (double)car_jam_left_to_right / (double)now_time;//cars_lef_to_right.size();//
            jam_right_to_left = (double)car_jam_right_to_left / (double)now_time;//cars_right_to_left.size();//
            jam_turn_left = (double)car_jam_turn_left / (double)now_time;//cars_turn_left.size();//
            jam_turn_right = (double)car_jam_turn_right / (double)now_time;//cars_turn_right.size();//

            //更新游戏中元素的坐标
            updatePosition();
        }
        if(play_again){
            play_again = false;
            Dialog* w = new Dialog;
            w->show();
            close();
        }
        //重新绘制图片
        update();
    });
}
void SimulateWindow::build_turn_right_Cars(){
    int t = rand() % 4;
    int num = cars_turn_right.count();
    bool flag = true;
    for(int i = 0; i < num; i++){
        if(cars_turn_right[i].m_Y >= GAME_HEIGHT - 1.1 * cars_turn_right[i].m_Car.height()){
            flag = false;
            break;
        }
    }
    if(flag){
        int num = cars_turn_right.count();
        Car c;
        if(t == 0){
            c = Car(CAR_PATH);
            c.car_type = 0;
        }
        else if (t == 1){
            c = Car(W_CAR_PATH);
            c.car_type = 1;
        }
        else if (t == 2){
            c = Car(R_CAR_PATH);
            c.car_type = 2;
        }
        else{
            c = Car(B_CAR_PATH);
            c.car_type = 3;
        }
        c.number = num;
        c.setSpeed(0, -3);
        //c.setPosition(TURN_LEFT_10_X + 10, GAME_HEIGHT);
        c.setPosition(GAME_WIDTH * 0.5 + 0.2 * ROAD_WIDTH, GAME_HEIGHT);
        cars_turn_right.append(c);
    }
    else turn_right_num++;
}
void SimulateWindow::build_left_to_right_Cars(){
    int t = rand() % 4;
    int num = cars_lef_to_right.count();
    bool flag = true;
    for(int i = 0; i < num; i++){
        if(cars_lef_to_right[i].m_X <= - 0.9 * CAR_HEIGHT){
            flag = false;
            break;
        }
    }
    if(flag){
        int num = cars_lef_to_right.count();
        Car c;
        if(t == 0){
            c = Car(CAR_TURN_90);
            c.car_type = 0;
        }
        else if(t == 1){
            c = Car(W_CAR_TURN_90);
            c.car_type = 1;
        }
        else if(t == 2){
            c = Car(R_CAR_TURN_90);
            c.car_type = 2;
        }
        else{
            c = Car(B_CAR_TURN_90);
            c.car_type = 3;
        }
        c.number = num;
        c.setSpeed(3, 0);
        c.setPosition(- 2 * CAR_HEIGHT, TURN_RIGHT_90_Y);
        cars_lef_to_right.append(c);
    }
    else left_to_right_num++;
}
void SimulateWindow::build_right_to_left_Cars(){
    int t = rand() % 4;
    int num = cars_right_to_left.count();
    bool flag = true;
    for(int i = 0; i < num; i++){
        if(cars_right_to_left[i].m_X >= 1600 - 1.1 * CAR_HEIGHT){
            flag = false;
            break;
        }
    }
    if(flag){
        int num = cars_right_to_left.count();
        Car c;
        if(t == 0){
            c = Car(CAR_TURN_090);
            c.car_type = 0;
        }
        else if(t == 1){
            c = Car(W_CAR_TURN_090);
            c.car_type = 1;
        }
        else if(t == 2){
            c = Car(R_CAR_TURN_090);
            c.car_type = 2;
        }
        else{
            c = Car(B_CAR_TURN_090);
            c.car_type = 3;
        }
        c.number = num;
        c.setSpeed(-3, 0);
        c.setPosition(1600, TURN_RIGHT_90_Y - 80);
        cars_right_to_left.append(c);
    }
    else right_to_left_num++;
}
void SimulateWindow::build_turn_left_Cars(){
    int t = rand() % 4;
    int num = cars_turn_left.count();
    bool flag = true;
    for(int i = 0; i < num; i++){
        if(cars_turn_left[i].m_Y >= GAME_HEIGHT - 1.1 * cars_turn_left[i].m_Car.height()){
            flag = false;
            break;
        }
    }
    if(flag){
        int num = cars_turn_left.count();
        Car c;
        if(t == 0){
            c = Car(CAR_PATH);
            c.car_type = 0;
        }
        else if(t == 1){
            c = Car(W_CAR_PATH);
            c.car_type = 1;
        }
        else if(t == 2){
            c = Car(R_CAR_PATH);
            c.car_type = 2;
        }
        else{
            c = Car(B_CAR_PATH);
            c.car_type = 3;
        }
        c.number = num;
        c.setSpeed(0, -3);
        //c.setPosition(GAME_WIDTH * 0.5 + 0.2 * ROAD_WIDTH, GAME_HEIGHT);
        c.setPosition(TURN_LEFT_10_X + 10, GAME_HEIGHT);
        cars_turn_left.append(c);
    }
    else turn_left_num++;
}

void SimulateWindow::updatePosition()
{
    //这一部分更新等待右转的车
    bool f = false;
    int num = cars_turn_right.count();
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < i; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turn_right[i].number) continue;
            if(cars_turn_right[i].judge_stop == 1){
                if ((cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y) * (cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y)
                        + (cars_turn_right[i].m_X + cars_turn_right[i].X_speed - cars_turn_right[j].m_X) * (cars_turn_right[i].m_X + cars_turn_right[i].X_speed- cars_turn_right[j].m_X)
                        <= cars_turn_right[i].m_Car.height() * cars_turn_right[i].m_Car.height() + cars_turn_right[i].m_Car.width() * cars_turn_right[i].m_Car.width()){
                    cars_turn_right[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
            else{
                if ((cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y) * (cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y)
                        + (cars_turn_right[i].m_X + cars_turn_right[i].X_speed - cars_turn_right[j].m_X) * (cars_turn_right[i].m_X + cars_turn_right[i].X_speed- cars_turn_right[j].m_X)
                        <= STOP_RATE * (cars_turn_right[i].m_Car.height() * cars_turn_right[i].m_Car.height() + cars_turn_right[i].m_Car.width() * cars_turn_right[i].m_Car.width())){
                    cars_turn_right[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
        }

        if(flag){//如果没有车与这辆车距离过近
            cars_turn_right[i].judge_stop = 1;
            if(cars_turn_right[i].m_Y >= ROAD_WIDTH + 50)cars_turn_right[i].m_Y += cars_turn_right[i].Y_speed;
            else{
                f = true;
            }
        }

    }
    if(heading) f = false;
    if(turning_right){
        turn_right_flag ++;
    }
    else if(f){
        turning_right_type = cars_turn_right[0].car_type;
        destruct_turn_right_cars();
        turn_right_flag ++;
        turning_right = true;
    }
    /*----------------------------------------------------------------------------------------------------------------------------
     * ---------------------------------------------------------------------------------------------------------------------------
     * ---------------------------------------------------------------------------------------------------------------------------*/
    //这一部分更新右转弯完毕的车
    f = false;
    num = cars_turned_right.count();
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turned_right[i].number) continue;
            if ((cars_turned_right[i].m_Y + cars_turned_right[i].Y_speed - cars_turned_right[j].m_Y) * (cars_turned_right[i].m_Y + cars_turned_right[i].Y_speed - cars_turned_right[j].m_Y)
                    + (cars_turned_right[i].m_X + cars_turned_right[i].X_speed - cars_turned_right[j].m_X) * (cars_turned_right[i].m_X + cars_turned_right[i].X_speed- cars_turned_right[j].m_X)
                    <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                flag = false;
                break;
            }
        }
        if(flag){//如果没有车与这辆车距离过近
            cars_turned_right[i].m_Y += cars_turned_right[i].Y_speed;
            cars_turned_right[i].m_X += cars_turned_right[i].X_speed;
        }
        if(cars_turned_right[i].m_X > 1600) f = true;
    }
    if(f) destruct_turned_right_cars();
    /*--------------------------------------------------------------------------------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------------*/
    //这一部分更新从左走向右的直行车辆
    f = false;
    num = cars_lef_to_right.count();
    heading = false;
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < i; j++){//判断是否有车与这辆车距离过近
            if(j == cars_lef_to_right[i].number) continue;
            if(cars_lef_to_right[i].judge_stop == 1){
                if ((cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y) * (cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y)
                        + (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed - cars_lef_to_right[j].m_X) * (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed- cars_lef_to_right[j].m_X)
                        <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                    cars_lef_to_right[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
            else{
                if ((cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y) * (cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y)
                        + (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed - cars_lef_to_right[j].m_X) * (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed- cars_lef_to_right[j].m_X)
                        <= STOP_RATE * (CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH)){
                    cars_lef_to_right[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
        }
        if(cars_lef_to_right[i].m_X >= 500 && cars_lef_to_right[i].m_X <= left_to_right_waitline + 2.2 * CAR_HEIGHT){
            if(turn_right_flag > 0) {flag = false; cars_lef_to_right[i].judge_stop = 0;}
            else heading = true;
        }
        if(flag){
            cars_lef_to_right[i].judge_stop = 1;
            if(light == 0){
                cars_lef_to_right[i].m_Y += cars_lef_to_right[i].Y_speed;
                cars_lef_to_right[i].m_X += cars_lef_to_right[i].X_speed;
            }
            else{
                if(cars_lef_to_right[i].m_X >= 410 || cars_lef_to_right[i].m_X <= 400){
                    cars_lef_to_right[i].m_Y += cars_lef_to_right[i].Y_speed;
                    cars_lef_to_right[i].m_X += cars_lef_to_right[i].X_speed;
                }
            }
        }
        if(cars_lef_to_right[i].m_X > 1600) f = true;
    }
    if(f) destruct_left_to_right_cars();
    /*--------------------------------------------------------------------------------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------------*/
    //这一部分更新从右到左的直行车辆
    f = false;
    num = cars_right_to_left.count();
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < i; j++){//判断是否有车与这辆车距离过近
            if(j == cars_right_to_left[i].number) continue;
            if(cars_right_to_left[i].judge_stop == 1){
                if ((cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y) * (cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y)
                        + (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed - cars_right_to_left[j].m_X) * (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed- cars_right_to_left[j].m_X)
                        <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                    cars_right_to_left[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
            else{
                if ((cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y) * (cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y)
                        + (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed - cars_right_to_left[j].m_X) * (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed- cars_right_to_left[j].m_X)
                        <= STOP_RATE * (CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH)){
                    cars_right_to_left[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
        }
        if(flag){//如果没有车与这辆车距离过近
            cars_right_to_left[i].judge_stop = 1;
            if(light == 0){
                cars_right_to_left[i].m_Y += cars_right_to_left[i].Y_speed;
                cars_right_to_left[i].m_X += cars_right_to_left[i].X_speed;
            }
            else{
                if(cars_right_to_left[i].m_X >= 980 || cars_right_to_left[i].m_X <= 970){
                    cars_right_to_left[i].m_Y += cars_right_to_left[i].Y_speed;
                    cars_right_to_left[i].m_X += cars_right_to_left[i].X_speed;
                }
            }
        }
        if(cars_right_to_left[i].m_X < - 2 * CAR_HEIGHT) f = true;
    }
    if(f) destruct_right_to_left_cars();
    /*------------------------------------------------------------------------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------------
    ------------------------------------------------------------------------------------------------------------------------*/
    //这一部分更新等待左转弯的车辆
    num = cars_turn_left.count();
    f = false;
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < i; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turn_left[i].number) continue;
            if(cars_turn_left[i].judge_stop == 1){
                if ((cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y) * (cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y)
                        + (cars_turn_left[i].m_X + cars_turn_left[i].X_speed - cars_turn_left[j].m_X) * (cars_turn_left[i].m_X + cars_turn_left[i].X_speed- cars_turn_left[j].m_X)
                        <= cars_turn_left[i].m_Car.height() * cars_turn_left[i].m_Car.height() + cars_turn_left[i].m_Car.width() * cars_turn_left[i].m_Car.width()){
                    cars_turn_left[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
            else{
                if ((cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y) * (cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y)
                        + (cars_turn_left[i].m_X + cars_turn_left[i].X_speed - cars_turn_left[j].m_X) * (cars_turn_left[i].m_X + cars_turn_left[i].X_speed- cars_turn_left[j].m_X)
                        <= STOP_RATE * (cars_turn_left[i].m_Car.height() * cars_turn_left[i].m_Car.height() + cars_turn_left[i].m_Car.width() * cars_turn_left[i].m_Car.width())){
                    cars_turn_left[i].judge_stop = 0;
                    flag = false;
                    break;
                }
            }
        }

        if(flag){//如果没有车与这辆车距离过近
            cars_turn_left[i].judge_stop = 1;
            if(light == 1){
                if(cars_turn_left[i].m_Y >= TURN_LEFT_10_Y + 10)cars_turn_left[i].m_Y += cars_turn_left[i].Y_speed;
                else{
                    f = true;
                }
            }
            else{
                if(cars_turn_left[i].m_Y >= ROAD_WIDTH + 150 || (cars_turn_left[i].m_Y <= ROAD_WIDTH + 145 && cars_turn_left[i].m_Y >= TURN_LEFT_10_Y + 10))cars_turn_left[i].m_Y += cars_turn_left[i].Y_speed;
                if(cars_turn_left[i].m_Y < TURN_LEFT_10_Y + 10) f = true;
            }
        }

    }
    if(turning_left){
        turn_left_flag ++;
    }
    else if(f){
        turning_left_type = cars_turn_left[0].car_type;
        destruct_turn_left_cars();
        turn_left_flag ++;
        turning_left = true;
    }
    /*------------------------------------------------------------------------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------------
    ------------------------------------------------------------------------------------------------------------------------*/
    //这一部分更新左转完毕的车
    f = false;
    num = cars_turned_left.count();
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turned_left[i].number) continue;
            if ((cars_turned_left[i].m_Y + cars_turned_left[i].Y_speed - cars_turned_left[j].m_Y) * (cars_turned_left[i].m_Y + cars_turned_left[i].Y_speed - cars_turned_left[j].m_Y)
                    + (cars_turned_left[i].m_X + cars_turned_left[i].X_speed - cars_turned_left[j].m_X) * (cars_turned_left[i].m_X + cars_turned_left[i].X_speed- cars_turned_left[j].m_X)
                    <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                flag = false;
                break;
            }
        }
        if(flag){//如果没有车与这辆车距离过近
            cars_turned_left[i].m_Y += cars_turned_left[i].Y_speed;
            cars_turned_left[i].m_X += cars_turned_left[i].X_speed;
        }
        if(cars_turned_left[i].m_X < - 2 * CAR_HEIGHT) f = true;
    }
    if(f) destruct_turned_left_cars();
}



void SimulateWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //这一部分处理右转车辆
    if(turn_right_flag >= 54){
        turning_right = false;
        turn_right_flag = 0;
        int num = cars_turned_right.count();
        Car c;
        if(turning_right_type == 0)c = Car(CAR_TURN_90);
        if(turning_right_type == 1)c = Car(W_CAR_TURN_90);
        if(turning_right_type == 2)c = Car(R_CAR_TURN_90);
        if(turning_right_type == 3)c = Car(B_CAR_TURN_90);
        c.car_type = turning_right_type;
        c.number = num;
        c.setPosition(TURN_RIGHT_90_X, TURN_RIGHT_90_Y);
        c.setSpeed(3, 0);
        cars_turned_right.append(c);
    }
    //这一部分处理左转车辆
    if(turn_left_flag >= 54){
        turning_left = false;
        turn_left_flag = 0;
        int num = cars_turned_left.count();
        Car c;
        if(turning_left_type == 0)c = Car(CAR_TURN_090);
        if(turning_left_type == 1)c = Car(W_CAR_TURN_090);
        if(turning_left_type == 2)c = Car(R_CAR_TURN_090);
        if(turning_left_type == 3)c = Car(B_CAR_TURN_090);
        c.car_type = turning_right_type;
        c.number = num;
        c.setPosition(TURN_LEFT_90_X, TURN_LEFT_90_Y);
        c.setSpeed(-3, 0);
        cars_turned_left.append(c);
    }
    //----------------------------------------------------------------------------------------------------------------

    //绘制地图
    painter.drawPixmap(0, 0, m_map.m_map1);
    int num = cars_turn_right.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_turn_right[i].m_X, cars_turn_right[i].m_Y, cars_turn_right[i].m_Car);
    }
    num = cars_turned_right.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_turned_right[i].m_X, cars_turned_right[i].m_Y, cars_turned_right[i].m_Car);
    }
    num = cars_lef_to_right.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_lef_to_right[i].m_X, cars_lef_to_right[i].m_Y, cars_lef_to_right[i].m_Car);
    }
    num = cars_right_to_left.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_right_to_left[i].m_X, cars_right_to_left[i].m_Y, cars_right_to_left[i].m_Car);
    }
    num = cars_turn_left.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_turn_left[i].m_X, cars_turn_left[i].m_Y, cars_turn_left[i].m_Car);
    }
    num = cars_turned_left.count();
    for(int i = 0; i < num; i++){
        painter.drawPixmap(cars_turned_left[i].m_X, cars_turned_left[i].m_Y, cars_turned_left[i].m_Car);
    }
    //----------------------------------------------------------------------------------------------------------------
    if(turn_right_flag > 0 && turn_right_flag < 54){
        if(turning_right_type == 0)painter.drawPixmap(car_turning_right[turn_right_flag / 6].m_X, car_turning_right[turn_right_flag / 6].m_Y, car_turning_right[turn_right_flag / 6].m_Car);
        if(turning_right_type == 1)painter.drawPixmap(w_car_turning_right[turn_right_flag / 6].m_X, w_car_turning_right[turn_right_flag / 6].m_Y, w_car_turning_right[turn_right_flag / 6].m_Car);
        if(turning_right_type == 2)painter.drawPixmap(r_car_turning_right[turn_right_flag / 6].m_X, r_car_turning_right[turn_right_flag / 6].m_Y, r_car_turning_right[turn_right_flag / 6].m_Car);
        if(turning_right_type == 3)painter.drawPixmap(b_car_turning_right[turn_right_flag / 6].m_X, b_car_turning_right[turn_right_flag / 6].m_Y, b_car_turning_right[turn_right_flag / 6].m_Car);
    }
    if(turn_left_flag > 0 && turn_left_flag < 54){
        if(turning_left_type == 0)painter.drawPixmap(car_turning_left[turn_left_flag / 6].m_X, car_turning_left[turn_left_flag / 6].m_Y, car_turning_left[turn_left_flag / 6].m_Car);
        if(turning_left_type == 1)painter.drawPixmap(w_car_turning_left[turn_left_flag / 6].m_X, w_car_turning_left[turn_left_flag / 6].m_Y, w_car_turning_left[turn_left_flag / 6].m_Car);
        if(turning_left_type == 2)painter.drawPixmap(r_car_turning_left[turn_left_flag / 6].m_X, r_car_turning_left[turn_left_flag / 6].m_Y, r_car_turning_left[turn_left_flag / 6].m_Car);
        if(turning_left_type == 3)painter.drawPixmap(b_car_turning_left[turn_left_flag / 6].m_X, b_car_turning_left[turn_left_flag / 6].m_Y, b_car_turning_left[turn_left_flag / 6].m_Car);
    }
    if(light == 0){
        painter.drawPixmap(turn_left_red.m_X, turn_left_red.m_Y, turn_left_red.m_Light);
        painter.drawPixmap(left_to_right_green.m_X, left_to_right_green.m_Y, left_to_right_green.m_Light);
        painter.drawPixmap(right_to_left_green.m_X, right_to_left_green.m_Y, right_to_left_green.m_Light);
    }
    else if(light == 1){
        painter.drawPixmap(turn_left_green.m_X, turn_left_green.m_Y, turn_left_green.m_Light);
        painter.drawPixmap(left_to_right_red.m_X, left_to_right_red.m_Y, left_to_right_red.m_Light);
        painter.drawPixmap(right_to_left_red.m_X, right_to_left_red.m_Y, right_to_left_red.m_Light);
    }
    else{
        if(judge_yellow_light == 1){
            painter.drawPixmap(turn_left_yellow.m_X, turn_left_yellow.m_Y, turn_left_yellow.m_Light);
            painter.drawPixmap(left_to_right_red.m_X, left_to_right_red.m_Y, left_to_right_red.m_Light);
            painter.drawPixmap(right_to_left_red.m_X, right_to_left_red.m_Y, right_to_left_red.m_Light);
        }
        else{
            painter.drawPixmap(turn_left_red.m_X, turn_left_red.m_Y, turn_left_red.m_Light);
            painter.drawPixmap(left_to_right_yellow.m_X, left_to_right_yellow.m_Y, left_to_right_yellow.m_Light);
            painter.drawPixmap(right_to_left_yellow.m_X, right_to_left_yellow.m_Y, right_to_left_yellow.m_Light);
        }
    }
    painter.drawPixmap(768, -5, light_struct);
    painter.drawPixmap(586, 116, light_struct);
    painter.drawPixmap(1048, 116, light_struct);
//    painter.drawPixmap(410, 116, car_turning_right[8].m_Car);
//    painter.drawPixmap(970, 116, car_turning_left[8].m_Car);
}

