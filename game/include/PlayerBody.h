#ifndef PLAYER_BODY_H
#define PLAYER_BODY_H

#include <string>
#include <memory>

#include "GameObject.h"
#include "Component.h"
#include "Timer.h"
#include "Gun.h"

using std::string;
using std::weak_ptr;


#define PLAYER_BODY_T "PlayerBody"

class PlayerBody : public Component {
public:
    PlayerBody(GameObject& associated, weak_ptr<GameObject> player);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void Shoot(float angle);
    void DropGun();
    void SetGun(Gun* gun);
    Gun* GetGun();

private:
    MoveState state;

    Gun *gun;

    weak_ptr<GameObject> player;
    //int offset = 0;
    Timer shootCooldownTimer;

};


#endif // PLAYER_BODY_H
