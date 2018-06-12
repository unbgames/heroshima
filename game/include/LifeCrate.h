//
// Created by edgar on 29/05/18.
//

#ifndef HEALTHCRATE_H
#define HEALTHCRATE_H


#include "Crate.h"

class LifeCrate : public Crate {
public:
    explicit LifeCrate(GameObject &associated, const Vec2 &initialPosition, int health, bool startFalling = true);

protected:
    void onCatch() override;

private:
    int health;

};


#endif //SRC_HEALTHCRATE_H
