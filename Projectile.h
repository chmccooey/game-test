#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "DisplayObject.h"

class Projectile : public DisplayObject
{
public:
    Projectile();
    Projectile(float x, float y, float direction, float speed); //direction in degrees

    void setSpeed(float direction, float speed);
    void updateLoop();

private:
    float m_xspeed;
    float m_yspeed;
};

#endif // PROJECTILE_H
