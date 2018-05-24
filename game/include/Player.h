#ifndef PLAYER_H
#define PLAYER_H

#include "Vec2.h"
#include "PlayerBody.h"
#include "Component.h"
#include "Sprite.h"

#define PLAYER_SPEED  100
#define JUMP_SPEED    400
#define GRAVITY       50.0f
#define PLAYER_T "Player"

class Player : public Component {

    enum MoveState { WALKING, RESTING };
    enum JumpState { JUMPING, FALLING, COLLIDING };
    MoveState movementState;
    JumpState jumpState;
    weak_ptr<GameObject> pBody;

    Vec2 speed;
    float verticalSpeed;
    float horizontalSpeed;

public:
    Player(GameObject& associated);
    ~Player();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    static Player* player;
};


#endif // PLAYER_H
