#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "GameObjectFactory.h"

class Player;

class GameWindow : public QGraphicsView {
Q_OBJECT
public:
    GameWindow(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private slots:
    void gameLoop();

private:
    QGraphicsScene scene;
    QTimer timer;
    GameObjectFactory factory;

    bool leftPressed = false;
    bool rightPressed = false;
    Player* playerPtr = nullptr;
};

#endif // GAMEWINDOW_H
