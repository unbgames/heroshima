//
// Created by edgar on 16/05/18.
//

#ifndef MENU_CLASS
#define MENU_CLASS

#define MENU_TYPE "Menu"
#define LABEL_NEW_GAME "Novo Jogo"
#define LABEL_CONTROLS "Controles"
#define LABEL_EXIT_GAME "Sair"


#include "Rect.h"
#include "Text.h"
#include "Sprite.h"

class Menu : public Component {
public:
    Menu(GameObject &associated);
    ~Menu();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    int GetOption();
    bool IsSelected();
    void SetSelected(bool s);

    enum { NEW_GAME, CONTROLS, EXIT_GAME };
    
private:
    vector<Text*> options;
    int optSelected;
    bool selected;

    GameObject controles;
    bool showControles;

    int FindOption(const string &optionText);
};


#endif //SRC_MENU_H
