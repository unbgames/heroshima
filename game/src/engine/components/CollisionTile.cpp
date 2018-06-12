#include <string>

#include "CollisionTile.h"

using std::string;


CollisionTile::CollisionTile(GameObject &associated) : Component(associated) {

}

void CollisionTile::Render() {

}

void CollisionTile::Update(float dt) {

}

bool CollisionTile::Is(string type) {
    return type == COLLISION_TILE_T;
}