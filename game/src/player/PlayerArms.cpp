#include <string>
#include <memory>
#include <Animation.h>
#include <LineTween.h>
#include <PeriodicEvent.h>
#include <RotationTween.h>
#include <WeaponCrate.h>
#include <Sound.h>
#include <Player.h>
#include <Sprite.h>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "SpriteSheet.h"

using std::string;
using std::weak_ptr;

PlayerArms::PlayerArms(GameObject &associated, weak_ptr<GameObject> player) : Component(associated), player(*player.lock()), isAttacking(false) {

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
    if (player.IsDead()) {
        associated.RequestDelete();
        return;
    }

    associated.box = player.box;
    associated.orientation = player.orientation;
    if(Player::player){
        movementState = Player::player->getMovementState();
        jumpState = Player::player->getJumpState();
    }

    if (InputManager::GetInstance().IsKeyDown(SPACE_BAR_KEY)) {
        isAttacking = true;
        if(shootCooldownTimer.Get() >= gun->getCooldownTime() && (gun->getAmmo() > 0 || gun->getAmmo() == -1)) {
            int shootAngle = (player.orientation == Orientation::LEFT ? 180 : 0);
            Shoot(shootAngle);
            shootCooldownTimer.Restart();

            if(gun->getAmmo() != -1) {
                gun->decrementAmmo();
            }
        }

    } else {
        isAttacking = false;
        auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
        Sprite* playerSprite = (Sprite*)player.GetComponent(SPRITE_TYPE);
        sprite->SetFrame(playerSprite->GetCurrentFrame());
    }

    if(movementState == CROUCH){
        associated.box.y += gun->getSpriteCrouch().offset;
        if(isAttacking) associated.box.x += associated.orientation == RIGHT ? 10 : -10;
    }

    //THIS IS A F#$@* PIECE OF SHIT
    if(!isAttacking){
        if(jumpState == JUMPING){
            associated.box.y -= 8;
        } else if(jumpState == FALLING){
            associated.box.x += associated.orientation == RIGHT ? 5 : -5;
            associated.box.y -= 16;
        } else if (jumpState == LANDING){
            associated.box.x += associated.orientation == RIGHT ? 10 : -10;
        }

    }

    if(gun == SpriteSheet::heavy && gun->getAmmo() <= 0){
        DropGun();
        SetGun(SpriteSheet::pistol);
    }

    shootCooldownTimer.Update(dt);
}

void PlayerArms::Render() {

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    string file;
    int frameCount = 0;
    float frameTime = 0;
    if(movementState == IDLE){
        if(!isAttacking){
            file = gun->getSpriteRest().sprite;
            frameCount = gun->getSpriteRest().frameCount;
            frameTime = gun->getSpriteRest().frameTime;
        } else{
            file = gun->getSpriteShoot().sprite;
            frameCount = gun->getSpriteShoot().frameCount;
            frameTime = gun->getSpriteShoot().frameTime;
        }
    } else if (movementState == WALKING || movementState == BLOCKED_LEFT || movementState == BLOCKED_RIGHT) {
        if(!isAttacking) {
            file = gun->getSpriteWalk().sprite;
            frameCount = gun->getSpriteWalk().frameCount;
            frameTime = gun->getSpriteWalk().frameTime;
        } else {
            file = gun->getSpriteShoot().sprite;
            frameCount = gun->getSpriteShoot().frameCount;
            frameTime = gun->getSpriteShoot().frameTime;
        }

    } else if (movementState == CROUCH) {
        if(!isAttacking){
            file = gun->getSpriteCrouch().sprite;
            frameCount = gun->getSpriteCrouch().frameCount;
            frameTime = gun->getSpriteCrouch().frameTime;
        } else{
            file = gun->getSpriteShoot().sprite;
            frameCount = gun->getSpriteShoot().frameCount;
            frameTime = gun->getSpriteShoot().frameTime;
        }
    }

    if(jumpState == JUMPING || jumpState == FALLING){
        if(!isAttacking){
            if(jumpState == JUMPING){
                file = "img/hiro/jump_up_arms.png";
                frameTime = 0.16f;
            } else if(jumpState == FALLING){
                file = file = gun->getSpriteRest().sprite;
                frameTime = 0.1f;
            }
            frameCount = 4;

        } else{
            file = gun->getSpriteShoot().sprite;
            frameCount = gun->getSpriteShoot().frameCount;
            frameTime = gun->getSpriteShoot().frameTime;
        }
    } else if (jumpState == LANDING){
        if(!isAttacking){
            file = gun->getSpriteRest().sprite;
            frameTime = gun->getSpriteRest().frameTime;
            frameCount = gun->getSpriteRest().frameCount;

        } else{
            file = gun->getSpriteShoot().sprite;
            frameCount = gun->getSpriteShoot().frameCount;
            frameTime = gun->getSpriteShoot().frameTime;
        }
    }

    auto playerComp = (Player*) player.GetComponent(PLAYER_TYPE);
    if (playerComp != nullptr) {
        sprite->SetVisible(!playerComp->IsAttacking() || playerComp->IsTransformed());
    }

    sprite->Open(file);
    sprite->SetFrameCount(frameCount);
    sprite->SetFrameTime(frameTime);
}

bool PlayerArms::Is(string type) {
    return type == PLAYER_ARMS_TYPE;
}

void PlayerArms::Shoot(float angle) {
    auto bulletGo = new GameObject;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, gun->getProjectile().speed, gun->getDamage(), 1000, gun->getProjectile().sprite, gun->getProjectile().frameCount, gun->getProjectile().frameTime, false));
    if(associated.orientation == Orientation::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w - bulletGo->box.w - 8;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8 + (movementState == CROUCH ? gun->getSpriteCrouch().offset : 0);
    } else {
        bulletGo->box.x = associated.box.GetPos().x + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8 + (movementState == CROUCH ? gun->getSpriteCrouch().offset : 0);
    }
    auto sound(new Sound(*bulletGo, "audio/GUN SHOT.ogg"));
    sound->Play();
    Game::GetInstance().GetCurrentState().AddCollisionObject(bulletGo, { 1.0f, 0.3f }, { 20.0f, -5.0f });
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
