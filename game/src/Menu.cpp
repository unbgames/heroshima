//
// Created by edgar on 16/05/18.
//

#include <InputManager.h>
#include <Resources.h>
#include "Menu.h"

Menu::Menu(GameObject &associated) : Component(associated), selected(false), optSelected(0) {
    //Se atentar para a ordem de incersao
    //As opcoes devem estar na mesma posicao no enum
    auto startGO(new GameObject);
    startGO->box += associated.box.GetPos();
    Text *startText = new Text(*startGO, "font/JAPAN.ttf", 60, Text::TextStyle::BLENDED, "Start", {255, 255, 255, 255});
    options.emplace_back(startText);
    associated.AddComponent(startText);

    auto exitGO(new GameObject);
    exitGO->box += associated.box.GetPos() + Vec2(0, startGO->box.h);
    Text *exitText = new Text(*exitGO, "font/JAPAN.ttf", 60, Text::TextStyle::BLENDED, "Exit", {255, 255, 255, 255});
    options.emplace_back(exitText);
    associated.AddComponent(exitText);
}

Menu::~Menu() {
    Resources::ClearResources();
}

void Menu::Update(float dt){
    InputManager instance = InputManager::GetInstance();

    if(instance.KeyPress(UP_ARROW_KEY)){
        optSelected--;
        if(optSelected < 0) optSelected = (int)(options.size() - 1);
    } else if(instance.KeyPress(DOWN_ARROW_KEY)){
        optSelected++;
        if(optSelected == (int) options.size()) optSelected = 0;
    }
    if(instance.KeyPress(ENTER_KEY)){
        selected = true;
    }
}

void Menu::Render(){
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    for(unsigned int i = 0; i < options.size(); i++){
        if((int) i == optSelected){
            options[i]->setColor(red);
        } else{
            options[i]->setColor(white);
        }
    }
}

bool Menu::Is(string type) {
    return type == MENU_TYPE;
}

int Menu::GetOption(){
    return optSelected;
}

bool Menu::IsSelected(){
    return selected;
}

void Menu::SetSelected(bool selected){
    this->selected = selected;
}
