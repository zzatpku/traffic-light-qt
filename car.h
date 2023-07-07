#ifndef CAR_H
#define CAR_H
#include <QtWidgets>
#include <iostream>
#include <string.h>
using namespace std;
#include <string.h>
#include <QString>

class Car
{
public:
    Car();
    Car(int num);
    Car(const QString s);
    void setPosition(int x, int y);
    void setSpeed(double s_x, double s_y);

public:
    QPixmap m_Car;
    int number;
    int car_type;//0代表taxi， 1代表white
    int judge_stop;//0代表刚刚在停，1代表刚刚在行

    int m_X;
    int m_Y;

    double X_speed;
    double Y_speed;
    QRect m_Rect;
};

#endif // CAR_H
