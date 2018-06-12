//
// Created by edgar on 16/03/18.
//

#ifndef GAME_CLASS
#define GAME_CLASS

#include <iostream>
#include <stack>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

#define GAME_NAME "HEROshima"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720

#define ASSETS_PATH "assets/"


class Game {

public :
    Game(string title, int width, int height);
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer ();
    State& GetCurrentState();

    void Push(State *state);

    void Run();

    float GetDeltaTime();

private:
    void CalculateDeltaTime();

    int frameStart;
    float dt;

    static Game *instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    stack<unique_ptr<State>> stateStack;

};

#endif //SRC_GAME_H
