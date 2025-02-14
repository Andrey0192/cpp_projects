#include "Player.h"
#include "PlatformTile.h"
#include <QPainter>
#include <QList>

Player::Player() {
    velocity = QPointF(0, 0);
}

QRectF Player::boundingRect() const {
    return QRectF(-15, -15, 30, 30);  // квадратный игрок
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}

void Player::moveHorizontally(qreal dx) {
    velocity.setX(dx);
    setPos(x() + velocity.x(), y());

    QList<QGraphicsItem*> collisions = collidingItems();
    for (QGraphicsItem* item : collisions) {
        if (auto* platform = dynamic_cast<PlatformTile*>(item)) {
            QRectF playerRect = boundingRect().translated(pos());
            QRectF platformRect = platform->boundingRect().translated(platform->pos());

            // Проверка столкновения справа
            if (velocity.x() > 0 && playerRect.right() > platformRect.left() && playerRect.left() < platformRect.left()) {
                setX(platformRect.left() - boundingRect().width()/2);
                velocity.setX(0);
            }
            // Проверка столкновения слева
            if (velocity.x() < 0 && playerRect.left() < platformRect.right() && playerRect.right() > platformRect.right()) {
                setX(platformRect.right() + boundingRect().width()/2);
                velocity.setX(0);
            }
        }
    }
}

void Player::applyGravity() {
    if (!onGround) {
        velocity.setY(velocity.y() + gravity);
    }
    setPos(x(), y() + velocity.y());

    onGround = false;
    QList<QGraphicsItem*> collisions = collidingItems();
    for (QGraphicsItem* item : collisions) {
        if (auto* platform = dynamic_cast<PlatformTile*>(item)) {
            QRectF playerRect = boundingRect().translated(pos());
            QRectF platformRect = platform->boundingRect().translated(platform->pos());

            // Столкновение сверху платформы при падении
            if (velocity.y() > 0 && playerRect.bottom() > platformRect.top() && playerRect.top() < platformRect.top()) {
                setY(platformRect.top() - boundingRect().height()/2);
                velocity.setY(0);
                onGround = true;
            }
            // Столкновение снизу платформы при прыжке
            if (velocity.y() < 0 && playerRect.top() < platformRect.bottom() && playerRect.bottom() > platformRect.bottom()) {
                setY(platformRect.bottom() + boundingRect().height()/2);
                velocity.setY(0);
            }
        }
    }
}

void Player::jump() {
    if (onGround) {
        velocity.setY(-10);
        onGround = false;
    }
}

void Player::updateObject() {
    // доп действия
}
