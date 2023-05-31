#include "mainscene.h"
#include "config.h"
#include <QWidget>
#include <algorithm>
#include <random>
#include <QVector>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScene();
    car_stream_1 = 1;
    light = 0;
    car_turning_right[0] = Car(CAR_TURN_10);
    car_turning_right[0].setPosition(TURN_RIGHT_10_X, TURN_RIGHT_10_Y);
    car_turning_right[1] = Car(CAR_TURN_20);
    car_turning_right[1].setPosition(TURN_RIGHT_20_X, TURN_RIGHT_20_Y);
    car_turning_right[2] = Car(CAR_TURN_30);
    car_turning_right[2].setPosition(TURN_RIGHT_30_X, TURN_RIGHT_30_Y);
    car_turning_right[3] = Car(CAR_TURN_40);
    car_turning_right[3].setPosition(TURN_RIGHT_40_X, TURN_RIGHT_40_Y);
    car_turning_right[4] = Car(CAR_TURN_50);
    car_turning_right[4].setPosition(TURN_RIGHT_50_X, TURN_RIGHT_50_Y);
    car_turning_right[5] = Car(CAR_TURN_60);
    car_turning_right[5].setPosition(TURN_RIGHT_60_X, TURN_RIGHT_60_Y);
    car_turning_right[6] = Car(CAR_TURN_70);
    car_turning_right[6].setPosition(TURN_RIGHT_70_X, TURN_RIGHT_70_Y);
    car_turning_right[7] = Car(CAR_TURN_80);
    car_turning_right[7].setPosition(TURN_RIGHT_80_X, TURN_RIGHT_80_Y);
    car_turning_right[8] = Car(CAR_TURN_90);
    car_turning_right[8].setPosition(TURN_RIGHT_90_X, TURN_RIGHT_90_Y);
    //----------------------------------------------------------------------
    w_car_turning_right[0] = Car(W_CAR_TURN_10);
    w_car_turning_right[0].setPosition(TURN_RIGHT_10_X, TURN_RIGHT_10_Y);
    w_car_turning_right[1] = Car(W_CAR_TURN_20);
    w_car_turning_right[1].setPosition(TURN_RIGHT_20_X, TURN_RIGHT_20_Y);
    w_car_turning_right[2] = Car(W_CAR_TURN_30);
    w_car_turning_right[2].setPosition(TURN_RIGHT_30_X, TURN_RIGHT_30_Y);
    w_car_turning_right[3] = Car(W_CAR_TURN_40);
    w_car_turning_right[3].setPosition(TURN_RIGHT_40_X, TURN_RIGHT_40_Y);
    w_car_turning_right[4] = Car(W_CAR_TURN_50);
    w_car_turning_right[4].setPosition(TURN_RIGHT_50_X, TURN_RIGHT_50_Y);
    w_car_turning_right[5] = Car(W_CAR_TURN_60);
    w_car_turning_right[5].setPosition(TURN_RIGHT_60_X, TURN_RIGHT_60_Y);
    w_car_turning_right[6] = Car(W_CAR_TURN_70);
    w_car_turning_right[6].setPosition(TURN_RIGHT_70_X, TURN_RIGHT_70_Y);
    w_car_turning_right[7] = Car(W_CAR_TURN_80);
    w_car_turning_right[7].setPosition(TURN_RIGHT_80_X, TURN_RIGHT_80_Y);
    w_car_turning_right[8] = Car(W_CAR_TURN_90);
    w_car_turning_right[8].setPosition(TURN_RIGHT_90_X, TURN_RIGHT_90_Y);
    //------------------------------------------------------------------------
    car_turning_left[0] = Car(CAR_TURN_010);
    car_turning_left[0].setPosition(TURN_LEFT_10_X, TURN_LEFT_10_Y);
    car_turning_left[1] = Car(CAR_TURN_020);
    car_turning_left[1].setPosition(TURN_LEFT_20_X, TURN_LEFT_20_Y);
    car_turning_left[2] = Car(CAR_TURN_030);
    car_turning_left[2].setPosition(TURN_LEFT_30_X, TURN_LEFT_30_Y);
    car_turning_left[3] = Car(CAR_TURN_040);
    car_turning_left[3].setPosition(TURN_LEFT_40_X, TURN_LEFT_40_Y);
    car_turning_left[4] = Car(CAR_TURN_050);
    car_turning_left[4].setPosition(TURN_LEFT_50_X, TURN_LEFT_50_Y);
    car_turning_left[5] = Car(CAR_TURN_060);
    car_turning_left[5].setPosition(TURN_LEFT_60_X, TURN_LEFT_60_Y);
    car_turning_left[6] = Car(CAR_TURN_070);
    car_turning_left[6].setPosition(TURN_LEFT_70_X, TURN_LEFT_70_Y);
    car_turning_left[7] = Car(CAR_TURN_080);
    car_turning_left[7].setPosition(TURN_LEFT_80_X, TURN_LEFT_80_Y);
    car_turning_left[8] = Car(CAR_TURN_090);
    car_turning_left[8].setPosition(TURN_LEFT_90_X, TURN_LEFT_90_Y);
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
    turn_right_flag = 0;
    turn_left_flag = 0;
    turning_right = false;
    turning_left = false;
    heading = false;
}

MainScene::~MainScene()
{

}

void MainScene::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //设置图标资源
    setWindowIcon(QIcon( GAME_ICON));
    //定时器设置
    m_Timer.setInterval(GAME_RATE);
}
void MainScene::destruct_turn_right_cars(){
    for(int i = 1; i < cars_turn_right.count(); i++)cars_turn_right[i].number--;
    cars_turn_right.pop_front();
}
void MainScene::destruct_turned_right_cars(){
    for(int i = 1; i < cars_turned_right.count(); i++)cars_turned_right[i].number--;
    cars_turned_right.pop_front();
}
void MainScene::destruct_left_to_right_cars(){
    for(int i = 1; i < cars_lef_to_right.count(); i++)cars_lef_to_right[i].number--;
    cars_lef_to_right.pop_front();
}
void MainScene::destruct_right_to_left_cars(){
    for(int i = 1; i < cars_right_to_left.count(); i++)cars_right_to_left[i].number--;
    cars_right_to_left.pop_front();
}
void MainScene::destruct_turn_left_cars(){
    for(int i = 1; i < cars_turn_left.count(); i++)cars_turn_left[i].number--;
    cars_turn_left.pop_front();
}
void MainScene::destruct_turned_left_cars(){
    for(int i = 1; i < cars_turned_left.count(); i++)cars_turned_left[i].number--;
    cars_turned_left.pop_front();
}
void MainScene::playGame()
{
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        int t = clock();
        t = t % 30000;
        if(t <=13000) light = 0;
        else if(15000 <= t && t <= 28000) light = 1;
        else{
            light = 2;
            if(t < 15000) judge_yellow_light = 0;
            else judge_yellow_light = 1;
        }
        int ran1 = rand() % (400 * car_stream_1);
        int ran2 = rand() % (400 * car_stream_1);
        int ran3 = rand() % (400 * car_stream_1);
        int ran4 = rand() % (400 * car_stream_1);
        if(ran1 == 0)
            build_left_to_right_Cars();
        if(ran2 == 0)
            build_turn_right_Cars();
        if(ran3 == 0)
            build_right_to_left_Cars();
        if(ran4 == 0)
            build_turn_left_Cars();
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
    });
}
void MainScene::build_turn_right_Cars(){
    int t = rand() % 2;
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
        else{
            c = Car(W_CAR_PATH);
            c.car_type = 1;
        }
        c.number = num;
        c.setSpeed(0, -3);
        c.setPosition(GAME_WIDTH * 0.5 + 0.2 * ROAD_WIDTH, GAME_HEIGHT);
        cars_turn_right.append(c);
    }
}
void MainScene::build_left_to_right_Cars(){
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
        Car c(CAR_TURN_90);
        c.number = num;
        c.setSpeed(3, 0);
        c.setPosition(- 2 * CAR_HEIGHT, TURN_RIGHT_90_Y);
        cars_lef_to_right.append(c);
    }
}
void MainScene::build_right_to_left_Cars(){
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
        Car c(CAR_TURN_090);
        c.number = num;
        c.setSpeed(-3, 0);
        c.setPosition(1600, TURN_RIGHT_90_Y - 80);
        cars_right_to_left.append(c);
    }
}
void MainScene::build_turn_left_Cars(){
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
        Car c(num);
        c.setSpeed(0, -3);
        c.setPosition(TURN_LEFT_10_X + 10, GAME_HEIGHT);
        cars_turn_left.append(c);
    }
}

void MainScene::updatePosition()
{
    //这一部分更新等待右转的车
    bool f = false;
    int num = cars_turn_right.count();
    for(int i = 0; i < num; i++){
        bool flag = true;
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turn_right[i].number) continue;
            if ((cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y) * (cars_turn_right[i].m_Y + cars_turn_right[i].Y_speed - cars_turn_right[j].m_Y)
                    + (cars_turn_right[i].m_X + cars_turn_right[i].X_speed - cars_turn_right[j].m_X) * (cars_turn_right[i].m_X + cars_turn_right[i].X_speed- cars_turn_right[j].m_X)
                    <= cars_turn_right[i].m_Car.height() * cars_turn_right[i].m_Car.height() + cars_turn_right[i].m_Car.width() * cars_turn_right[i].m_Car.width()){
                flag = false;
                break;
            }
        }

        if(flag){//如果没有车与这辆车距离过近
            if(cars_turn_right[i].m_Y >= ROAD_WIDTH + 50)cars_turn_right[i].m_Y += cars_turn_right[i].Y_speed;
            else{
                f = true;
            }
        }

    }
    if(heading) f = false;
    if(turning_right){
        turn_right_flag++;
    }
    else if(f){
        turning_right_type = cars_turn_right[0].car_type;
        destruct_turn_right_cars();
        turn_right_flag++;
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
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_lef_to_right[i].number) continue;
            if ((cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y) * (cars_lef_to_right[i].m_Y + cars_lef_to_right[i].Y_speed - cars_lef_to_right[j].m_Y)
                    + (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed - cars_lef_to_right[j].m_X) * (cars_lef_to_right[i].m_X + cars_lef_to_right[i].X_speed- cars_lef_to_right[j].m_X)
                    <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                flag = false;
                break;
            }
        }
        if(cars_lef_to_right[i].m_X >= 500 && cars_lef_to_right[i].m_X <= left_to_right_waitline + 2.2 * CAR_HEIGHT){
            if(turn_right_flag > 0) flag = false;
            else heading = true;
        }
        if(flag){
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
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_right_to_left[i].number) continue;
            if ((cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y) * (cars_right_to_left[i].m_Y + cars_right_to_left[i].Y_speed - cars_right_to_left[j].m_Y)
                    + (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed - cars_right_to_left[j].m_X) * (cars_right_to_left[i].m_X + cars_right_to_left[i].X_speed- cars_right_to_left[j].m_X)
                    <= CAR_HEIGHT * CAR_HEIGHT + CAR_WIDTH * CAR_WIDTH){
                flag = false;
                break;
            }
        }
        if(flag){//如果没有车与这辆车距离过近
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
        for(int j = 0; j < num; j++){//判断是否有车与这辆车距离过近
            if(j == cars_turn_left[i].number) continue;
            if ((cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y) * (cars_turn_left[i].m_Y + cars_turn_left[i].Y_speed - cars_turn_left[j].m_Y)
                    + (cars_turn_left[i].m_X + cars_turn_left[i].X_speed - cars_turn_left[j].m_X) * (cars_turn_left[i].m_X + cars_turn_left[i].X_speed- cars_turn_left[j].m_X)
                    <= cars_turn_left[i].m_Car.height() * cars_turn_left[i].m_Car.height() + cars_turn_left[i].m_Car.width() * cars_turn_left[i].m_Car.width()){
                flag = false;
                break;
            }
        }

        if(flag){//如果没有车与这辆车距离过近
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
        turn_left_flag++;
    }
    else if(f){
        destruct_turn_left_cars();
        turn_left_flag++;
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

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

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
    if(turn_right_flag >= 54){
        turning_right = false;
        turn_right_flag = 0;
        int num = cars_turned_right.count();
        Car c;
        if(turning_right_type == 0)c = Car(CAR_TURN_90);
        if(turning_right_type == 1)c = Car(W_CAR_TURN_90);
        c.car_type = turning_right_type;
        c.number = num;
        c.setPosition(TURN_RIGHT_90_X, TURN_RIGHT_90_Y);
        c.setSpeed(3, 0);
        cars_turned_right.append(c);
    }
    if(turn_right_flag > 0 && turn_right_flag < 54){
        if(turning_right_type == 0)painter.drawPixmap(car_turning_right[turn_right_flag / 6].m_X, car_turning_right[turn_right_flag / 6].m_Y, car_turning_right[turn_right_flag / 6].m_Car);
        if(turning_right_type == 1)painter.drawPixmap(w_car_turning_right[turn_right_flag / 6].m_X, w_car_turning_right[turn_right_flag / 6].m_Y, w_car_turning_right[turn_right_flag / 6].m_Car);
    }
    if(turn_left_flag >= 54){
        turning_left = false;
        turn_left_flag = 0;
        int num = cars_turned_left.count();
        Car c(CAR_TURN_090);
        c.number = num;
        c.setPosition(TURN_LEFT_90_X, TURN_LEFT_90_Y);
        c.setSpeed(-3, 0);
        cars_turned_left.append(c);
    }
    if(turn_left_flag > 0 && turn_left_flag < 54){
        painter.drawPixmap(car_turning_left[turn_left_flag / 6].m_X, car_turning_left[turn_left_flag / 6].m_Y, car_turning_left[turn_left_flag / 6].m_Car);
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
}
