#ifndef CAR_H
#define CAR_H
#include <QtWidgets>
#include <iostream>
#include <string.h>

class Car
{
public:
    Car();
    Car(int num);
    Car(char s[]);
    void setPosition(int x, int y);
    void setSpeed(int s_x, int s_y);

public:
    QPixmap m_Car;
    int number;

    int m_X;
    int m_Y;

    int X_speed;
    int Y_speed;
    QRect m_Rect;
};

#endif // CAR_H
