//
// Created by edgar on 16/05/18.
//

#include <InputManager.h>
#include <Resources.h>
#include <Sprite.h>
#include "Menu.h"

Menu::Menu(GameObject &associated) : Component(associated), selected(false), optSelected(0) {
    showControles = false;
    //Se atentar para a ordem de incersao
    //As opcoes devem estar na mesma posicao no enum
    auto startGO(new GameObject);
    startGO->box += associated.box.GetPos();
    Text *startText = new Text(*startGO, "font/JAPAN.ttf", 60, Text::TextStyle::BLENDED, LABEL_NEW_GAME, {255, 255, 255, 255});
    options.emplace_back(startText);
    associated.AddComponent(startText);

    auto controlsGO(new GameObject);
    controlsGO->box += associated.box.GetPos() + Vec2(0, startGO->box.h);
    Text *controlsText = new Text(*controlsGO, "font/JAPAN.ttf", 60, Text::TextStyle::BLENDED, LABEL_CONTROLS, {255, 255, 255, 255});
    options.emplace_back(controlsText);
    associated.AddComponent(controlsText);

    controles.AddComponent(new Sprite(controles, "img/image.png"));
    controles.box += {controlsGO->box.x + controlsGO->box.w + 20, controlsGO->box.y};

    auto exitGO(new GameObject);
    exitGO->box += associated.box.GetPos() + Vec2(0, startGO->box.h + controlsGO->box.h);
    Text *exitText = new Text(*exitGO, "font/JAPAN.ttf", 60, Text::TextStyle::BLENDED, LABEL_EXIT_GAME, {255, 255, 255, 255});
    options.emplace_back(exitText);
    associated.AddComponent(exitText);
}

Menu::~Menu() {
    Resources::ClearResources();
}

void Menu::Update(float dt){
    InputManager inputManager = InputManager::GetInstance();

    if(inputManager.KeyPress(UP_ARROW_KEY)){
        optSelected--;
        if(optSelected < 0) optSelected = (int)(options.size() - 1);
    } else if(inputManager.KeyPress(DOWN_ARROW_KEY)){
        optSelected++;
        if(optSelected == (int) options.size()) optSelected = 0;
    }

    for (auto &option : options) {
        if(option->GetAssociatedBox().Contains(inputManager.GetMouse())){
            optSelected = FindOption(option->getText());
            if(inputManager.MouseRelease(LEFT_MOUSE_BUTTON) || inputManager.KeyPress(ENTER_KEY)){
                selected = true;
                break;
            }
        } else{
            if(inputManager.KeyPress(ENTER_KEY)){
                selected = true;
                break;
            }

        }
    }

    showControles = optSelected == CONTROLS;
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
    if(showControles) controles.Render();
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

int Menu::FindOption(const string &optionText) {
    if(optionText == LABEL_NEW_GAME){
        return NEW_GAME;
    } else if(optionText == LABEL_CONTROLS){
        return CONTROLS;
    } else if(optionText == LABEL_EXIT_GAME){
        return EXIT_GAME;
    }
}
