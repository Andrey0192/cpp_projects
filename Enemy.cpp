#include "Enemy.h"
#include "PlatformTile.h"
#include <QPainter>
#include <QList>

Enemy::Enemy() {
    velocity = QPointF(2, 0);  // Начальная скорость вправо
}

QRectF Enemy::boundingRect() const {
    return QRectF(-15, -15, 30, 30);  // квадратный враг
}

void Enemy::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
}

void Enemy::updateObject() {
    // движение туда сюда
    setPos(x() + velocity.x(), y());

    //  Проверка границ сцены
    if (x() > 700) {
        velocity.setX(-speed);
    }
    if (x() < 100) {
        velocity.setX(speed);
    }

    // Проверка столкновений с платформами 
    QList<QGraphicsItem*> collisions = collidingItems();
    for (QGraphicsItem* item : collisions) {
        if (auto* platform = dynamic_cast<PlatformTile*>(item)) {
            QRectF enemyRect = boundingRect().translated(pos());
            QRectF platformRect = platform->boundingRect().translated(platform->pos());

            // Столкновение справа
            if (velocity.x() > 0 && enemyRect.right() > platformRect.left() && enemyRect.left() < platformRect.left()) {
                setX(platformRect.left() - boundingRect().width()/2);
                velocity.setX(-speed);
            }
            // Столкновение слева
            if (velocity.x() < 0 && enemyRect.left() < platformRect.right() && enemyRect.right() > platformRect.right()) {
                setX(platformRect.right() + boundingRect().width()/2);
                velocity.setX(speed);
            }
        }
    }
}
