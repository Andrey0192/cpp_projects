#include "GameWindow.h"
#include "Player.h"
#include "LevelLoader.h"
#include "Enemy.h"
#include "Item.h"
#include <QKeyEvent>
#include <QDebug>

GameWindow::GameWindow(QWidget* parent)
        : QGraphicsView(parent)
{
    setScene(&scene);
    setFixedSize(800, 600);
    scene.setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(Qt::white);  // Установка белого фона для видимости

    // Загрузка уровня
    LevelLoader loader(&scene, &factory);
    if (!loader.loadFromFile("level.txt")) {  // Убедитесь, что файл находится в рабочей директории
        qWarning() << "4Не удалось загрузить уровень!";
    }

    // Найти игрока в сцене
    for (QGraphicsItem* item : scene.items()) {
        if (Player* p = dynamic_cast<Player*>(item)) {
            playerPtr = p;
            break;
        }
    }

    if (!playerPtr) {
        qWarning() << "3Игрок не найден в уровне!";
    }

    connect(&timer, &QTimer::timeout, this, &GameWindow::gameLoop);
    timer.start(16);  // ~60 FPS
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    if (!playerPtr) {
        QGraphicsView::keyPressEvent(event);
        return;
    }

    switch(event->key()) {
        case Qt::Key_Left:
            leftPressed = true;
            break;
        case Qt::Key_Right:
            rightPressed = true;
            break;
        case Qt::Key_Space:
            playerPtr->jump();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    switch(event->key()) {
        case Qt::Key_Left:
            leftPressed = false;
            break;
        case Qt::Key_Right:
            rightPressed = false;
            break;
        default:
            QGraphicsView::keyReleaseEvent(event);
    }
}

void GameWindow::gameLoop() {
    if (playerPtr) {
        qreal dx = 0;
        if (leftPressed) dx -= 5;
        if (rightPressed) dx += 5;
        if (dx != 0) playerPtr->moveHorizontally(dx);
        playerPtr->applyGravity();
    }

    // Обновление остальных объектов
    for (QGraphicsItem* item : scene.items()) {
        GameObject* obj = dynamic_cast<GameObject*>(item);
        if (obj && obj != playerPtr) {
            obj->updateObject();
        }
    }

    // Проверка столкновений игрока с врагами и предметами
    if (playerPtr) {
        QList<QGraphicsItem*> collisions = playerPtr->collidingItems();
        for (QGraphicsItem* item : collisions) {
            if (auto* enemy = dynamic_cast<Enemy*>(item)) {
                qDebug() << "1Столкновение с врагом!";
                // Здесь можно добавить логику уменьшения здоровья или завершения игры
            }
            if (auto* itemObj = dynamic_cast<Item*>(item)) {
                scene.removeItem(itemObj);
                delete itemObj;
                qDebug() << "2Предмет собран!";
                // Можно увеличить счёт или добавить в инвентарь
            }
        }
    }

    scene.update();
}
