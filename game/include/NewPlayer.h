//
// Created by edgar on 05/07/18.
//

#ifndef SRC_NEWPLAYER_H
#define SRC_NEWPLAYER_H

#define PLAYER_MAX_LIVES 9
#define PLAYER_SPEED  400

#define JUMP_SPEED    600

#define PLAYER_TYPE "Player"

#include "Timer.h"
#include "PlayerArms.h"
#include "Component.h"

class NewPlayer : public Component {
public:
    NewPlayer(GameObject &associated);
    ~NewPlayer();

    static NewPlayer* player;

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void Start() override;

    static PlayerArms* playerArms;

    int GetHp() const;
    void SetHp(int hp);
    void IncremmentHp();
    void DecrementHp();

    void NotifyCollision(GameObject &other) override;

    MoveState getMovementState();
    JumpState getJumpState();

private:
    StaticSprite currentSprite;

    MoveState movementState;
    JumpState jumpState;

    int hp;
    bool usedSecondJump, landed;
    bool isDamage;
    Timer landingTimer;

    Vec2 speed;
    float verticalSpeed;
    float horizontalSpeed;
};


#endif //SRC_NEWPLAYER_H
