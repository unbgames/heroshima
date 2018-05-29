//
// Created by edgar on 28/05/18.
//

#include <Player.h>
#include <Sound.h>
#include <Game.h>
#include "WeaponCrate.h"

WeaponCrate::WeaponCrate(GameObject &associated, const Vec2 &initialPosition, Gun* gun, bool startFalling) :
        Crate(associated, initialPosition, startFalling), gun(gun) {

}

void WeaponCrate::OnCatch() {
    gun->setAmmo(gun->getFull());
    Player::playerBody->SetGun(gun);
    associated.RequestDelete();

    //TODO garantir que esse GO eh deletado apos terminar de tocar o som
    auto bulletGO(new GameObject);
    auto sound(new Sound(*bulletGO, "audio/heavy_machine_gun.wav"));
    auto recharge(new Sound(*bulletGO, "audio/recarregar.ogg"));
    sound->Play();
    recharge->Play();

}
