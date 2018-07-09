//
// Created by edgar on 05/07/18.
//

#ifndef SRC_PLAYER_CLASS
#define SRC_PLAYER_CLASS

#define PLAYER_MAX_LIVES 9
#define PLAYER_SPEED  400

#define JUMP_SPEED  500

#define PLAYER_TYPE "Player"

#include "Timer.h"
#include "PlayerArms.h"
#include "Component.h"

class Player : public Component {
public:
    Player(GameObject &associated);
    ~Player();

    static Player* player;

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void Start() override;

    static PlayerArms* playerArms;

    int GetHp() const;
    BodyState GetBodyState() const;
    bool IsAttacking() const;
    void SetHp(int hp);
    void IncremmentHp();
    void DecrementHp();

    void NotifyCollision(GameObject &other) override;

    MoveState getMovementState();
    JumpState getJumpState();

    bool UseSword() const;


private:
    StaticSprite currentSprite;

    MoveState movementState;
    JumpState jumpState;
    BodyState bodyState;

    int hp;
    bool usedSecondJump, landed, useSword, playedDeathSound;

private:
    Timer landingTimer;
    Timer transformationTimer, swordTimer, deadTimer;

    Vec2 speed;
    float verticalSpeed;
    float horizontalSpeed;
};


#endif //SRC_PLAYER_CLASS
