#include "picture.h"
#include "config.h"

Picture::Picture(){}

Picture::Picture(const QString s)
{
    //初始化加载汽车图片资源
    m_Picture.load(s);

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 + 0.25 * ROAD_WIDTH;
    m_Y = GAME_HEIGHT - m_Picture.height();

    //初始化矩形框
    m_Rect.setWidth(m_Picture.width());
    m_Rect.setHeight(m_Picture.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Picture::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}
