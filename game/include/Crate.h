//
// Created by edgar on 28/05/18.
//

#ifndef WEAPONCRATE_H
#define WEAPONCRATE_H

#define WEAPON_CRATE_TYPE "Crate"


#include "Component.h"
#include "Gun.h"

class Crate : public Component{
public:
    //TODO make constructor protected
    Crate(GameObject &associated, Vec2 position);

    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

protected:
    Vec2 speed;
    Vec2 position;
    float verticalSpeed;

private:
    //Update(dt) must be private so that Crate's subclasses won't be able to override it
    void Update(float dt) override;

};


#endif //SRC_WEAPONCRATE_H
