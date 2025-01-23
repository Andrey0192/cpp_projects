#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <memory>
#include "GameObject.h"

enum class ObjectType { Player, Enemy, Item };

class GameObjectFactory {
public:
    GameObject* create(ObjectType type);
};

#endif // GAMEOBJECTFACTORY_H
