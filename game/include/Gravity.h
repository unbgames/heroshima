//
// Created by edgar on 29/05/18.
//

#ifndef SRC_GRAVITY_H
#define SRC_GRAVITY_H

#define GRAVITY 50.0f
#define GRAVITY_TYPE "Gravity"


#include "Component.h"

class Gravity : public Component {
public:
    Gravity(GameObject &associated);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    float GetVerticalSpeed() const;

private:
    Vec2 speed;
    float verticalSpeed;
};


#endif //SRC_GRAVITY_H
