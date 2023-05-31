#ifndef LIGHT_H
#define LIGHT_H
#include <QWidget>

class Light
{
public:
    Light();
    Light(QString s);
    void setPosition(int x, int y);

public:
    QPixmap m_Light;
    int m_X;
    int m_Y;
};

#endif // LIGHT_H
