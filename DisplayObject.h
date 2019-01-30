#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

class QPainter;

#include <QColor>
#include <QPointF>

class DisplayObject
{
public:
    DisplayObject();
    DisplayObject(float x, float y, const QColor &color);
    ~DisplayObject();

    float getX() const;
    float getY() const;

    void move(float x, float y);
    void moveX(float value);
    void moveY(float value);
    void setPos(float x, float y);
    void setColor(const QColor &color);

    void draw(QPainter* painter);

private:
    float m_x;
    float m_y;
    QColor m_color;
};

#endif // DISPLAYOBJECT_H
