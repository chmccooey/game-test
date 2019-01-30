#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QList>

class DisplayObject;
class Projectile;

class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

    void updateLoop();
    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);
    void centerPlayer();

protected:
    void mouseReleaseEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent* ev);

private:
    enum GameKeys
    {
        GameKey_MoveLeft = 0,
        GameKey_MoveRight,
        GameKey_MoveUp,
        GameKey_MoveDown,
        GameKey_Total
    };

private:
    bool m_keys[GameKey_Total];
    DisplayObject* m_player;
    QList<Projectile*> m_bullets;
};

#endif // GAMEVIEW_H
