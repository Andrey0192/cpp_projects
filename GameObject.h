#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>

class GameObject : public QGraphicsItem {
public:
    virtual void updateObject() = 0;
};

#endif // GAMEOBJECT_H
