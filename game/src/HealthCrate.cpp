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
//    auto recharge(new Sound(*catchGO, "audio/recarregar.ogg"));
//    recharge->Play();
//    catchGO->AddComponent(recharge);
//    catchGO->AddComponent(new Text(*catchGO, "font/Call me maybe.ttf", 60, Text::BLENDED, "1", {255,255,255,255}));
//    catchGO->AddComponent(new LineTween(*catchGO, 10,
//                                        associated.box.GetCenter() - catchGO->box.GetCenter(),
//                                        associated.box.GetCenter() - catchGO->box.GetCenter() + Vec2(0, -50),
//                                        [catchGO] {catchGO->RequestDelete();} ));
//
//    Game::GetInstance().GetCurrentState().AddObject(catchGO);

}
