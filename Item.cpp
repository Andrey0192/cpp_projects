#include "Item.h"
#include <QPainter>

Item::Item() {
}

QRectF Item::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}

void Item::updateObject() {
    // Логика обновления предмета 
}
