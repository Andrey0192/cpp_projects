#include "GameObjectFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

GameObject* GameObjectFactory::create(ObjectType type) {
    switch (type) {
        case ObjectType::Player:
            return new Player();
        case ObjectType::Enemy:
            return new Enemy();
        case ObjectType::Item:
            return new Item();
        default:
            return nullptr;
    }
}
