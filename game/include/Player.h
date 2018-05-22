//
// Created by edgar on 17/05/18.
//

#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#define PLAYER_SPEED 100
#define JUMP_SPEED   500
#define GRAVITY      50.0f

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
    void Shoot(float angle);

    static Player* player;

private:
    Vec2 speed;
    float verticalSpeed;
    float horizontalSpeed;
    bool onGround;
    bool walking;
    bool wasWalking;
    bool rightDirection;
    bool shooting;
    float shootingAngle;
    int hp;

};


#endif //SRC_PLAYER_H
