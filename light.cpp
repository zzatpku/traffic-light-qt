#include "light.h"
#include "config.h"

Light::Light()
{
}

Light::Light(QString str)
{
    //初始化加载汽车图片资源
    m_Light.load(str);

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 + 0.25 * ROAD_WIDTH;
    m_Y = GAME_HEIGHT - m_Light.height();

}

void Light::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
}

