//
// Created by edgar on 16/05/18.
//

#ifndef SRC_MENU_H
#define SRC_MENU_H

#define MENU_TYPE "Menu"

#include "Rect.h"
#include "Text.h"

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

    enum { START, EXIT };
    
private:
    vector<Text*> options;
    int optSelected;
    bool selected;
};


#endif //SRC_MENU_H
