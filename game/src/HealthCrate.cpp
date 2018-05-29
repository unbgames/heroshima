//
// Created by edgar on 29/05/18.
//

#include <Sprite.h>
#include <Sound.h>
#include <Text.h>
#include <Player.h>
#include <LineTween.h>
#include <Game.h>
#include <Camera.h>
#include "HealthCrate.h"

HealthCrate::HealthCrate(GameObject &associated, const Vec2 &initialPosition, int health, bool startFalling) :
        Crate(associated, initialPosition, startFalling), health(health) {
    Sprite* lifeCrateImg = new Sprite(associated, "img/life_item.png");
    associated.AddComponent(lifeCrateImg);

    if(startFalling) {
        associated.box.y = -3*associated.box.h;
    } else{
        associated.box.y = initialPosition.y;
    }
}

void HealthCrate::onCatch() {
    associated.RequestDelete();

    //FIXME colocar o texto alinhado corretamente na tela
//    auto catchGO(new GameObject);
//    catchGO->box.x = associated.box.x - Player::player->GetAssociatedBox().x;
//    catchGO->box.y = associated.box.y - Player::player->GetAssociatedBox().y;
//
//    cout<<associated.box.toString()<<endl;
//    cout<<Player::player->GetAssociatedBox().toString()<<endl;
//    cout<<catchGO->box.toString()<<endl;
//
//    auto recharge(new Sound(*catchGO, "audio/recarregar.ogg"));
//    recharge->Play();
//    catchGO->AddComponent(recharge);
//    catchGO->AddComponent(new Text(*catchGO, "font/Call me maybe.ttf", 250, Text::BLENDED, "+1", {255,255,255,255}));
//
//    Animation* animation = new LineTween(*catchGO, 1,
//                                         associated.box.GetCenter(),
//                                         associated.box.GetCenter() + Vec2(0, -50),
//                                         [catchGO] {catchGO->RequestDelete();} );
//
//    catchGO->AddComponent(animation);
//
//    Game::GetInstance().GetCurrentState().AddObject(catchGO);

}
