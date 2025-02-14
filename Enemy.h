#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include <QPointF>
#include <QPainter>

class Enemy : public GameObject {
public:
    Enemy();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void updateObject() override;

private:
    QPointF velocity;
    qreal speed = 2.0;
};

#endif // ENEMY_H
