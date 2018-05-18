//
// Created by edgar on 17/05/18.
//

#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#define PLAYER_SPEED 200

#include "Vec2.h"
#include "Component.h"
#include <Sprite.h>

class Player :public Component {
public:
    Player(GameObject &associated);
    virtual ~Player();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    static Player* player;

private:
    Vec2 speed;
    float linearSpeed;
    float angle;
    bool andando;
    bool estavaAndando;
    bool direita;
    int hp;

};


#endif //SRC_PLAYER_H
