#include "GameView.h"
#include "Projectile.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <cmath>

GameView::GameView(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < GameKey_Total; i++)
        m_keys[i] = false;
    m_player = new DisplayObject(width() / 2, height() / 2, QColor(100, 150, 100)); //put player in the center of the screen
    m_bullets = QList<Projectile*>(); //empty list
}
GameView::~GameView()
{
    int i, size;

    delete m_player;
    size = m_bullets.size();
    for (i = 0; i < size; i++)
        delete m_bullets.at(i);
    m_bullets.clear();
}

//keyboard and mouse events
void GameView::keyPressEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_Left: m_keys[GameKey_MoveLeft] = true; break;
    case Qt::Key_Right: m_keys[GameKey_MoveRight] = true; break;
    case Qt::Key_Up: m_keys[GameKey_MoveUp] = true; break;
    case Qt::Key_Down: m_keys[GameKey_MoveDown] = true; break;
    }
}
void GameView::keyReleaseEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_Left: m_keys[GameKey_MoveLeft] = false; break;
    case Qt::Key_Right: m_keys[GameKey_MoveRight] = false; break;
    case Qt::Key_Up: m_keys[GameKey_MoveUp] = false; break;
    case Qt::Key_Down: m_keys[GameKey_MoveDown] = false; break;
    }
}
void GameView::mouseReleaseEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        float direction, speed = 12.0f, px, py;

        px = m_player->getX();
        py = m_player->getY();
        direction = atan2f(static_cast<float>(ev->y()) - py, static_cast<float>(ev->x()) - px);
        direction *= 57.2958f; //convert from radians to degrees
        Projectile* proj = new Projectile(px, py, direction, speed);
        m_bullets.push_back(proj);
    }
}

void GameView::centerPlayer()
{
    m_player->setPos(static_cast<float>(width()) * 0.5f, static_cast<float>(height()) * 0.5f);
}
void GameView::updateLoop()
{
    int size, i, x, y, screen_width = width(), screen_height = height();

    //move player
    const float speed = 4.0f;
    if (m_keys[GameKey_MoveLeft])
        m_player->moveX(-speed);
    else if (m_keys[GameKey_MoveRight])
        m_player->moveX(speed);
    if (m_keys[GameKey_MoveUp])
        m_player->moveY(-speed);
    else if (m_keys[GameKey_MoveDown])
        m_player->moveY(speed);

    //update bullet locations
    size = m_bullets.size();
    for (i = 0; i < size; i++)
        m_bullets.at(i)->updateLoop();

    //remove bullets that escape the screen
    Projectile* bullet;
    for (i = size - 1; i >= 0; i--)
    {
        bullet = m_bullets.at(i);
        x = static_cast<int>(bullet->getX());
        y = static_cast<int>(bullet->getY());
        if (x < 0 || x > screen_width || y < 0 || y > screen_height)
        {
            delete bullet;
            m_bullets.removeAt(i);
        }
    }
    update();
}

//draw function that draws the game scene
void GameView::paintEvent(QPaintEvent* ev)
{
    QWidget::paintEvent(ev);

    int size, i;
    QPainter painter(this);
    QPen pen = QPen();
    QBrush brush = QBrush();

    //draw the background
    brush.setColor(QColor(0, 0, 0));
    brush.setStyle(Qt::SolidPattern);
    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0, 0, width(), height());

    //draw the bullets
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255));
    painter.setPen(pen);
    size = m_bullets.size();
    for (i = 0; i < size; i++)
        m_bullets.at(i)->draw(&painter);

    //draw the player
    m_player->draw(&painter);
    painter.end();
}
