#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include <QPainter>

class Item : public GameObject {
public:
    Item();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void updateObject() override;
};

#endif // ITEM_H
