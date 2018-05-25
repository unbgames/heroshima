#include <string>
#include <memory>

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

    gun = Weapons::heavy;

    this->player = player;
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.AddComponent(new Collider(associated));
    Sprite* img = new Sprite(associated, gun->getSpriteRest().sprite, gun->getSpriteRest().frameCount, gun->getSpriteRest().frameTime);
    associated.orientation = playerGO.orientation;
    associated.box = {
            (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL + playerGO.box.GetCenter().x - img->GetWidth() / 2,
            BODY_OFFSET_VERTICAL + playerGO.box.y - img->GetHeight(),
            img->GetWidth(),
            img->GetHeight()
    };
    associated.AddComponent(img);
}

void PlayerBody::Start() {}

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
            int shootAngle = (playerGO.orientation == GameObject::LEFT ? 180 : 0);
            Shoot(shootAngle);
            shootCooldownTimer.Restart();

            if(gun->getAmmo() != -1) {
                gun->decrementAmmo();
            }

            cout << "ammo: "<<gun->getAmmo() << endl;
            offset = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * gun->getSpriteShoot().offset;
        }

    } else {
        state = RESTING;
        offset = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * gun->getSpriteRest().offset;
    }

    if(gun->getType() == GunType::HEAVY && gun->getAmmo() <= 0){
        gun = Weapons::pistol;
        cout << "Troca de arma" << endl;
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
    if(associated.orientation == GameObject::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 + bulletGo->box.h - 7;
    } else {
        bulletGo->box.x = associated.box.GetPos().x - associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h - 7;
    }
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, gun->getProjectile().speed, gun->getDamage(), 1000, gun->getProjectile().sprite, gun->getProjectile().frameCount, gun->getProjectile().frameTime, true));
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}

Gun *PlayerBody::getGun() const {
    return gun;
}
