//
// Created by edgar on 05/07/18.
//

#ifndef SRC_NEWPLAYER_H
#define SRC_NEWPLAYER_H

#define PLAYER_MAX_LIVES 9

#define PLAYER_TYPE "Player"

#include "Component.h"

class NewPlayer : public Component {
public:
    NewPlayer(GameObject &associated);
    ~NewPlayer();

    static NewPlayer* player;

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;


    int GetHp() const;
    void SetHp(int hp);
    void IncremmentHp();
    void DecrementHp();

private:
    StaticSprite currentSprite;

    MoveState movementState;
    JumpState jumpState;
    AttackingState attackingState;

    int hp;
    bool usedSecondJump;

};


#endif //SRC_NEWPLAYER_H
