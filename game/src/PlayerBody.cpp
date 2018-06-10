#include <string>
#include <memory>
#include <Animation.h>
#include <LineTween.h>
#include <PeriodicEvent.h>
#include <RotationTween.h>
#include <WeaponCrate.h>
#include <Sound.h>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "Player.h"
#include "Weapons.h"

using std::string;
using std::weak_ptr;

PlayerBody::PlayerBody(GameObject &associated, weak_ptr<GameObject> player) : Component(associated) {

    gun = Weapons::pistol;

    this->player = player;
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    Sprite* img = new Sprite(associated, gun->getSpriteRest().sprite, gun->getSpriteRest().frameCount, gun->getSpriteRest().frameTime);
    associated.orientation = playerGO.orientation;
    associated.box.w = img->GetWidth();
    associated.box.y = img->GetWidth();
    associated.AddComponent(img);
}

void PlayerBody::Start() {
}

void PlayerBody::Update(float dt) {
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {//FIXME segfault
        associated.RequestDelete();
    }

    associated.box = playerGO.box;
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
        }

    } else {
        if(Player::player->getMovementState() == WALKING){
            state = WALKING;
        } else if(Player::player->getMovementState() == RESTING){
            state = RESTING;
        }
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

    } else if(state == WALKING){
        sprite->Open(gun->getSpriteWalk().sprite);
        sprite->SetFrameCount(gun->getSpriteWalk().frameCount);
        sprite->SetFrameTime(gun->getSpriteWalk().frameTime);
    }
    //FIXME setar frames para evitar descontinuação ao atirar
}

bool PlayerBody::Is(string type) {
    return type == PLAYER_BODY_T;
}

void PlayerBody::Shoot(float angle) {
    auto bulletGo = new GameObject;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, gun->getProjectile().speed, gun->getDamage(), 1000, gun->getProjectile().sprite, gun->getProjectile().frameCount, gun->getProjectile().frameTime, false));
    if(associated.orientation == Orientation::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w - bulletGo->box.w - 8;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8;
    } else {
        bulletGo->box.x = associated.box.GetPos().x + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8;
    }
    auto sound(new Sound(*bulletGo, "audio/tiro.ogg"));
    sound->Play();
    Game::GetInstance().GetCurrentState().AddCollisionObject(bulletGo);
}

void PlayerBody::DropGun() {
    auto troca(new GameObject);
    Sprite* img;

    //TODO place here other's weapons logic
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
