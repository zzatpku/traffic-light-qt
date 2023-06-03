#ifndef PICTURE_H
#define PICTURE_H
#include<QtWidgets>

class Picture
{
public:
    Picture();
    Picture(const QString s);
    void setPosition(int x, int y);
public:
    QPixmap m_Picture;

    int m_X;
    int m_Y;

    QRect m_Rect;
};

#endif // PICTURE_H
