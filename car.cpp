#include "car.h"
#include "config.h"

Car::Car()
{
    //初始化加载汽车图片资源
    m_Car.load(CAR_PATH);
    judge_stop = 1;

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 + 0.25 * ROAD_WIDTH;
    m_Y = GAME_HEIGHT - m_Car.height();

    //初始化矩形框
    m_Rect.setWidth(m_Car.width());
    m_Rect.setHeight(m_Car.height());
    m_Rect.moveTo(m_X,m_Y);

}
Car::Car(const QString str)
{
    //初始化加载汽车图片资源
    m_Car.load(str);
    judge_stop = 1;

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 + 0.25 * ROAD_WIDTH;
    m_Y = GAME_HEIGHT - m_Car.height();

    //初始化矩形框
    m_Rect.setWidth(m_Car.width());
    m_Rect.setHeight(m_Car.height());
    m_Rect.moveTo(m_X,m_Y);

}

Car::Car(int num)
{
    number = num;
    //初始化加载飞机图片资源
    m_Car.load(CAR_PATH);

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 + 0.2 * ROAD_WIDTH;
    m_Y = GAME_HEIGHT - m_Car.height();

    //初始化矩形框
    m_Rect.setWidth(m_Car.width());
    m_Rect.setHeight(m_Car.height());
    m_Rect.moveTo(m_X,m_Y);

}

void Car::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}

void Car::setSpeed(double s_x, double s_y)
{
    X_speed = s_x;
    Y_speed = s_y;
}
