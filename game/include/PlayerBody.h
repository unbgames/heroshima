#ifndef PLAYER_BODY_H
#define PLAYER_BODY_H

#include <string>
#include <memory>

#include "GameObject.h"
#include "Component.h"

using std::string;
using std::weak_ptr;


#define PLAYER_BODY_T "PlayerBody"
#define BODY_OFFSET_VERTICAL 8
#define BODY_OFFSET_HORIZONTAL 5

class PlayerBody : public Component {

enum BodyState { RESTING, SHOOTING };
BodyState state;

weak_ptr<GameObject> player;

public:
    PlayerBody(GameObject& associated, weak_ptr<GameObject> player);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void Shoot(float angle);
};


#endif // PLAYER_BODY_H
