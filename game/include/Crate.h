//
// Created by edgar on 28/05/18.
//

#ifndef WEAPONCRATE_H
#define WEAPONCRATE_H

#define CRATE_TYPE "Crate"
#define CRATE_OFFSET 400


#include "Component.h"

class Crate : public Component{
public:

    void Render() override;
    bool Is(string type) override;

protected:
    explicit Crate(GameObject &associated, Vec2 initialPosition, bool startFalling = true);

    virtual void onCatch() = 0;

private:
    //These must be private so that Crate's subclasses won't be able to override them
    void Update(float dt) override;
    void NotifyCollision(GameObject &other) override;
    Vec2 speed;
    float verticalSpeed;

};


#endif //SRC_WEAPONCRATE_H
