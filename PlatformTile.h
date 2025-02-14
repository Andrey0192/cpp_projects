#ifndef PLATFORMTILE_H
#define PLATFORMTILE_H

#include <QGraphicsRectItem>

class PlatformTile : public QGraphicsRectItem {
public:
    PlatformTile(qreal x, qreal y, qreal width, qreal height);
};

#endif // PLATFORMTILE_H
