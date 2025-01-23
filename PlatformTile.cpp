#include "PlatformTile.h"
#include <QBrush>
#include <QPen>  // Добавлено включение QPen

PlatformTile::PlatformTile(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsRectItem(x, y, width, height)
{
    setBrush(QBrush(Qt::darkGray));
    setPen(QPen(Qt::NoPen));  // Передаём объект QPen
}
