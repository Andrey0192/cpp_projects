#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QString>
#include <QGraphicsScene>
#include "GameObjectFactory.h"

class LevelLoader {
public:
    LevelLoader(QGraphicsScene* scene, GameObjectFactory* factory);
    bool loadFromFile(const QString& filename);
private:
    QGraphicsScene* scene;
    GameObjectFactory* factory;
};

#endif // LEVELLOADER_H
