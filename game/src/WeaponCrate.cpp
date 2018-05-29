//
// Created by edgar on 28/05/18.
//

#include <Player.h>
#include "WeaponCrate.h"

WeaponCrate::WeaponCrate(GameObject &associated, const Vec2 &initialPosition, Gun* gun, bool startFalling) :
        Crate(associated, initialPosition, startFalling), gun(gun) {

}

void WeaponCrate::OnCatch() {
    Player::playerBody->SetGun(gun);
    associated.RequestDelete();
}
