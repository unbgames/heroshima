#include <string>
#include <memory>
#include <Animation.h>
#include <LineTween.h>
#include <PeriodicEvent.h>
#include <RotationTween.h>
#include <Crate.h>
#include <WeaponCrate.h>
#include <Sound.h>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Player.h"
#include "Weapons.h"

using std::string;
using std::weak_ptr;

PlayerBody::PlayerBody(GameObject &associated, weak_ptr<GameObject> player)
    : Component(associated) {

    gun = Weapons::pistol;

    this->player = player;
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.AddComponent(new Collider(associated));
    Sprite* img = new Sprite(associated, gun->getSpriteRest().sprite, gun->getSpriteRest().frameCount, gun->getSpriteRest().frameTime);
    associated.orientation = playerGO.orientation;
    associated.box = {
            (playerGO.orientation == Orientation::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL + playerGO.box.GetCenter().x - img->GetWidth() / 2,
            BODY_OFFSET_VERTICAL + playerGO.box.y - img->GetHeight(),
            (float)img->GetWidth(),
            (float)img->GetHeight()
    };
    associated.AddComponent(img);
}

void PlayerBody::Start() {
}

void PlayerBody::Update(float dt) {
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.box.x = offset + playerGO.box.GetCenter().x - associated.box.w / 2;
    associated.box.y = BODY_OFFSET_VERTICAL + playerGO.box.y - associated.box.h;
    associated.orientation = playerGO.orientation;

    if (InputManager::GetInstance().IsKeyDown(SPACE_BAR_KEY)) {
        if(shootCooldownTimer.Get() >= gun->getCooldownTime() && (gun->getAmmo() > 0 || gun->getAmmo() == -1)) {
            state = SHOOTING;
            int shootAngle = (playerGO.orientation == Orientation::LEFT ? 180 : 0);
            Shoot(shootAngle);
            shootCooldownTimer.Restart();

            if(gun->getAmmo() != -1) {
                gun->decrementAmmo();
            }

            cout << "ammo: "<<gun->getAmmo() << endl;
            offset = (playerGO.orientation == Orientation::LEFT ? -1 : 1) * gun->getSpriteShoot().offset;
        }

    } else {
        state = RESTING;
        offset = (playerGO.orientation == Orientation::LEFT ? -1 : 1) * gun->getSpriteRest().offset;
    }

    if(gun == Weapons::heavy && gun->getAmmo() <= 0){
        DropGun();
        SetGun(Weapons::pistol);
    }

    shootCooldownTimer.Update(dt);
}

void PlayerBody::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (state == SHOOTING) {
        sprite->Open(gun->getSpriteShoot().sprite);
        sprite->SetFrameCount(gun->getSpriteShoot().frameCount);
        sprite->SetFrameTime(gun->getSpriteShoot().frameTime);

    } else if (state == RESTING) {
        sprite->Open(gun->getSpriteRest().sprite);
        sprite->SetFrameCount(gun->getSpriteRest().frameCount);
        sprite->SetFrameTime(gun->getSpriteRest().frameTime);
    }
}

bool PlayerBody::Is(string type) {
    return type == PLAYER_BODY_T;
}

void PlayerBody::Shoot(float angle) {
    auto bulletGo = new GameObject;
    if(associated.orientation == Orientation::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 + bulletGo->box.h - 7;
    } else {
        bulletGo->box.x = associated.box.GetPos().x - associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h - 7;
    }
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, gun->getProjectile().speed, gun->getDamage(), 1000, gun->getProjectile().sprite, gun->getProjectile().frameCount, gun->getProjectile().frameTime, true));
    auto sound(new Sound(*bulletGo, "audio/tiro.ogg"));
    sound->Play();
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}

void PlayerBody::DropGun() {
    auto troca(new GameObject);
    Sprite* img;

    //TODO fazer a lógica para as demais armas aqui
    if(gun == Weapons::heavy){
        img = new Sprite(*troca, "img/heavy_machine_gun.png");
    } else{
        img = new Sprite(*troca, "img/heavy_machine_gun.png");
    }

    Animation* animation = new LineTween(*troca, 1,
                                     associated.box.GetCenter() - troca->box.GetCenter(),
                                     associated.box.GetCenter() - troca->box.GetCenter() + Vec2((associated.orientation == Orientation::LEFT ? 75 : - 75), -50),
                                     [troca] {troca->RequestDelete();} );

    Animation* rotation = new RotationTween(*troca, 1,
            360, associated.orientation == Orientation::RIGHT ? Orientation::LEFT : Orientation ::RIGHT);

    PeriodicEvent* blink = new PeriodicEvent(*troca, 0.1,
                                             [img] {img->SetVisible(false);},
                                             [img] {img->SetVisible(true);});

    troca->orientation = associated.orientation;
    troca->AddComponent(img);
    troca->AddComponent(blink);
    troca->AddComponent(animation);
    troca->AddComponent(rotation);
    Game::GetInstance().GetCurrentState().AddObject(troca);
}

void PlayerBody::SetGun(Gun *gun) {
    this->gun = gun;
    //FIXME garantir que esse GO eh deletado apos terminar de tocar o som
    auto bulletGO(new GameObject);
    auto recharge(new Sound(*bulletGO, "audio/recarregar.ogg"));
    recharge->Play();
}

Gun* PlayerBody::GetGun() {
    return this->gun;
}
