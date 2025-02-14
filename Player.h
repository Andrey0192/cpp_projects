#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <QPointF>
#include <QPainter>

class Player : public GameObject {
public:
    Player();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void updateObject() override;
    void moveHorizontally(qreal dx);
    void applyGravity();
    void jump();

    QPointF velocity;
    const qreal gravity = 0.5;
    bool onGround = false;
};

#endif // PLAYER_H
