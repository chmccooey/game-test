#include "Projectile.h"
#include <cmath>

#define D2R 0.01745329251f //converts from degrees to radians

Projectile::Projectile()
    :DisplayObject(0.0f, 0.0f, QColor(255, 150, 0))
{
    setSpeed(0.0f, 1.0f);
}
Projectile::Projectile(float x, float y, float direction, float speed) //direction in degrees
    :DisplayObject(x, y, QColor(255, 150, 0))
{
    setSpeed(direction, speed);
}

void Projectile::setSpeed(float direction, float speed)
{
    m_xspeed = cosf(direction * D2R) * speed;
    m_yspeed = sinf(direction * D2R) * speed;
}
void Projectile::updateLoop()
{
    move(m_xspeed, m_yspeed);
}
