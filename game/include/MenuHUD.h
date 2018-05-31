//
// Created by edgar on 31/05/18.
//

#ifndef MENUHUD_H
#define MENUHUD_H

#define MENU_HUD_TYPE "MenuHUD"
#define MARGIN_TOP 10

#include "Component.h"
#include "Clock.h"
#include "Text.h"

class MenuHUD : public Component {
public:
    explicit MenuHUD(GameObject &associated, bool isClock = true);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    Clock* clock;
    Text* clockText;

    bool isClock;

    void AddClock();
};


#endif //SRC_MENUHUD_H
