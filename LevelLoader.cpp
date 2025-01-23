#include "LevelLoader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "PlatformTile.h"

LevelLoader::LevelLoader(QGraphicsScene* scene, GameObjectFactory* factory)
        : scene(scene), factory(factory) {}

bool LevelLoader::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    int y = 0;
    qreal tileSize = 40.0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        for (int x = 0; x < line.length(); ++x) {
            QChar ch = line.at(x);
            qreal posX = x * tileSize;
            qreal posY = y * tileSize;

            if (ch == '#') {
                PlatformTile* tile = new PlatformTile(posX, posY, tileSize, tileSize);
                scene->addItem(tile);
            } else if (ch == 'P') {
                auto player = factory->create(ObjectType::Player);
                if (player) {
                    player->setPos(posX + tileSize/2, posY + tileSize/2);
                    scene->addItem(player);
                }
            } else if (ch == 'E') {
                auto enemy = factory->create(ObjectType::Enemy);
                if (enemy) {
                    enemy->setPos(posX + tileSize/2, posY + tileSize/2);
                    scene->addItem(enemy);
                }
            } else if (ch == 'I') {
                auto item = factory->create(ObjectType::Item);
                if (item) {
                    item->setPos(posX + tileSize/2, posY + tileSize/2);
                    scene->addItem(item);
                }
            }
            // Обработка других символов по необходимости
        }
        ++y;
    }
    return true;
}
