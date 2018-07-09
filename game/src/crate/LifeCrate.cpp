//
// Created by edgar on 29/05/18.
//

#include <Sprite.h>
#include <Sound.h>
#include <Text.h>
#include <LineTween.h>
#include <Game.h>
#include <PeriodicEvent.h>
#include <Player.h>
#include "LifeCrate.h"

LifeCrate::LifeCrate(GameObject &associated, const Vec2 &initialPosition, int health, bool startFalling) :
        Crate(associated, initialPosition, startFalling), health(health) {
    Sprite* lifeCrateImg = new Sprite(associated, "img/medkit.png", 9, 0.15);
    associated.AddComponent(lifeCrateImg);

    if(startFalling) {
        associated.box.y = -3*associated.box.h;
    } else{
        associated.box.y = initialPosition.y;
    }
}

void LifeCrate::onCatch() {
    associated.RequestDelete();

    auto catchGO(new GameObject);
    auto recharge(new Sound(*catchGO, "audio/COLETA VIDA.ogg"));
    recharge->Play();
    catchGO->AddComponent(recharge);
    Text *text = new Text(*catchGO, "font/Japanese.ttf", 30, Text::BLENDED, "+" + to_string(health), {255, 255, 255, 255});
    catchGO->AddComponent(text);
    catchGO->AddComponent(new LineTween(*catchGO, 1.5,
                                        associated.box.GetCenter() - catchGO->box.GetCenter(),
                                        associated.box.GetCenter() - catchGO->box.GetCenter() + Vec2(0, -50),
                                        [catchGO] {catchGO->RequestDelete();} ));

    catchGO->AddComponent(new PeriodicEvent(*catchGO, 0.1,
                                             [text] {text->SetAlpha(0);},
                                             [text] {text->SetAlpha(255);}, 0.1, 0.5));

    Player::player->SetHp(Player::player->GetHp() + health);

    Game::GetInstance().GetCurrentState().AddObject(catchGO);

}
