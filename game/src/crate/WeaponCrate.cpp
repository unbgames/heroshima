//
// Created by edgar on 28/05/18.
//

#include <Sound.h>
#include <Player.h>
#include "WeaponCrate.h"

WeaponCrate::WeaponCrate(GameObject &associated, const Vec2 &initialPosition, Gun* gun, bool startFalling) :
        Crate(associated, initialPosition, startFalling), gun(gun) {

}

void WeaponCrate::onCatch() {
    gun->setAmmo(gun->getFull());
    Player::playerArms->SetGun(gun);
    associated.RequestDelete();

    //FIXME garantir que esse GO eh deletado apos terminar de tocar o som
    auto bulletGO(new GameObject);
    auto sound(new Sound(*bulletGO, "audio/COLETA BALAS.ogg"));
    sound->Play();

}
