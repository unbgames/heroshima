//
// Created by edgar on 31/05/18.
//

#ifndef MENUHUD_H
#define MENUHUD_H

#define MENU_HUD_TYPE "MenuHUD"
#define MARGIN_TOP 10
#define MARGIN_LEFT 10

#include "Component.h"
#include "Clock.h"
#include "Text.h"

class MenuHUD : public Component {
public:
    explicit MenuHUD(GameObject &associated, bool isFace = true, bool isLifeIndicator = true, bool isClock = true);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    GameObject* faceGO;
    bool isFace;
    void AddFace();

    GameObject* lifeGO;
    bool isLife;
    void AddLifeIndicator();

    Clock* clock;
    GameObject* clockGO;
    bool isClock;
    void AddClock();

};


#endif //SRC_MENUHUD_H
