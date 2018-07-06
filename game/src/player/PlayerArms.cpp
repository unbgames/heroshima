#include <string>
#include <memory>
#include <Animation.h>
#include <LineTween.h>
#include <PeriodicEvent.h>
#include <RotationTween.h>
#include <WeaponCrate.h>
#include <Sound.h>
#include <NewPlayer.h>
#include <Sprite.h>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "SpriteSheet.h"

using std::string;
using std::weak_ptr;

PlayerArms::PlayerArms(GameObject &associated, weak_ptr<GameObject> player) : Component(associated), player(*player.lock()) {

    gun = SpriteSheet::pistol;

    Sprite* img = new Sprite(associated, gun->getSpriteRest().sprite, gun->getSpriteRest().frameCount, gun->getSpriteRest().frameTime);
    associated.orientation = this->player.orientation;
    associated.box.w = img->GetWidth();
    associated.box.h = img->GetHeight();
    associated.AddComponent(img);
}

void PlayerArms::Start() {
}

void PlayerArms::Update(float dt) {
    if (player.IsDead()) {//FIXME segfault
        associated.RequestDelete();
        return;
    }

    associated.box = player.box;
    associated.orientation = player.orientation;
    if (InputManager::GetInstance().IsKeyDown(SPACE_BAR_KEY)) {
        if (NewPlayer::player->getMovementState() == CROUCH){
            associated.box.y += 30;
            associated.box.x += (player.orientation == Orientation::LEFT ? -5 : 5);
        }
        if(shootCooldownTimer.Get() >= gun->getCooldownTime() && (gun->getAmmo() > 0 || gun->getAmmo() == -1)) {
//            state = SHOOTING;
            int shootAngle = (player.orientation == Orientation::LEFT ? 180 : 0);
            Shoot(shootAngle);
            shootCooldownTimer.Restart();

            if(gun->getAmmo() != -1) {
                gun->decrementAmmo();
            }
        }

    } else {
        auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
        Sprite* playerSprite = (Sprite*)player.GetComponent(SPRITE_TYPE);
        if (NewPlayer::player->getMovementState() == WALKING) {
            state = WALKING;
        } else if (NewPlayer::player->getMovementState() == RESTING) {
//            state = RESTING;

        } else if (NewPlayer::player->getMovementState() == CROUCH){
            state = CROUCH;
        }
        sprite->SetFrame(playerSprite->GetCurrentFrame());
    }

    if(gun == SpriteSheet::heavy && gun->getAmmo() <= 0){
        DropGun();
        SetGun(SpriteSheet::pistol);
    }

    shootCooldownTimer.Update(dt);
}

void PlayerArms::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (/*state == SHOOTING*/true) {
        sprite->Open(gun->getSpriteShoot().sprite);
        sprite->SetFrameCount(gun->getSpriteShoot().frameCount);
        sprite->SetFrameTime(gun->getSpriteShoot().frameTime);

    } else if (state == RESTING) {
        sprite->Open(gun->getSpriteRest().sprite);
        sprite->SetFrameCount(gun->getSpriteRest().frameCount);
        sprite->SetFrameTime(gun->getSpriteRest().frameTime);

    } else if (state == WALKING) {
        sprite->Open(gun->getSpriteWalk().sprite);
        sprite->SetFrameCount(gun->getSpriteWalk().frameCount);
        sprite->SetFrameTime(gun->getSpriteWalk().frameTime);

    } else if (state == CROUCH) {
        sprite->Open(gun->getSpriteCrouch().sprite);
        sprite->SetFrameCount(gun->getSpriteCrouch().frameCount);
        sprite->SetFrameTime(gun->getSpriteCrouch().frameTime);
    }
}

bool PlayerArms::Is(string type) {
    return type == PLAYER_ARMS_TYPE;
}

void PlayerArms::Shoot(float angle) {
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

void PlayerArms::DropGun() {
    auto troca(new GameObject);
    Sprite* img;

    //TODO place here other's weapons logic
    if(gun == SpriteSheet::heavy){
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

void PlayerArms::SetGun(Gun *gun) {
    this->gun = gun;
    //FIXME garantir que esse GO eh deletado apos terminar de tocar o som
    auto bulletGO(new GameObject);
    auto recharge(new Sound(*bulletGO, "audio/recarregar.ogg"));
    recharge->Play();
}

Gun* PlayerArms::GetGun() {
    return this->gun;
}

void PlayerArms::RequestDelete() {
    associated.RequestDelete();
}
