#ifndef COLLISION_TILE_H
#define COLLISION_TILE_H

#include <string>

#include "engine/Component.h"
#include "engine/GameObject.h"

#define COLLISION_TILE_T "CollisionTile"

using std::string;


class CollisionTile : public Component {

public:
    CollisionTile(GameObject& associated);

    void Render() override;
    void Update(float dt) override;
    bool Is(string file) override;
};


#endif // COLLISION_TILE_H
