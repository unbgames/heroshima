//
// Created by edgar on 28/05/18.
//

#ifndef SRC_WEAPONCRATE_H
#define SRC_WEAPONCRATE_H


#include "Crate.h"
#include "player/Gun.h"

class WeaponCrate : public Crate {
public:
    explicit WeaponCrate(GameObject &associated, const Vec2 &initialPosition, Gun* gun, bool startFalling = true);

protected:
    void onCatch() override;

private:
    Gun* gun;

};


#endif //SRC_WEAPONCRATE_H
