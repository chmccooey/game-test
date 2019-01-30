#include "DisplayObject.h"
#include <QPointF>
#include <QPainter>

DisplayObject::DisplayObject()
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_color = QColor(255, 255, 255); //default to white
}
DisplayObject::DisplayObject(float x, float y, const QColor &color)
{
    m_x = x;
    m_y = y;
    m_color = color;
}
DisplayObject::~DisplayObject()
{

}

float DisplayObject::getX() const
{
    return m_x;
}
float DisplayObject::getY() const
{
    return m_y;
}
void DisplayObject::move(float x, float y)
{
    m_x += x;
    m_y += y;
}
void DisplayObject::moveX(float value)
{
    m_x += value;
}
void DisplayObject::moveY(float value)
{
    m_y += value;
}
void DisplayObject::setPos(float x, float y)
{
    m_x = x;
    m_y = y;
}
void DisplayObject::setColor(const QColor &color)
{
    m_color = color;
}
void DisplayObject::draw(QPainter* painter)
{
    QBrush b = painter->brush();
    b.setColor(m_color);

    //draw a 32x32 rectangle as the display object, this will use bitmaps as the game is developed
    painter->setBrush(b);
    painter->drawRect(static_cast<int>(m_x) - 16, static_cast<int>(m_y) - 16, 32, 32);
}
