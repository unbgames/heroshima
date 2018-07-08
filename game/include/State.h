//
// Created by edgar on 10/05/18.
//

#ifndef STATE_CLASS
#define STATE_CLASS

#define MINIMUM_COLLIDER_DIST 70

#include "GameObject.h"
#include "../src/xml/pugixml.hpp"

class State {
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual weak_ptr<GameObject> AddObject(GameObject *go);
    virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);
    virtual weak_ptr<GameObject> AddTileObject(GameObject *go);
    virtual weak_ptr<GameObject> GetTileObjectPtr(GameObject *go);
    virtual weak_ptr<GameObject> AddCollisionObject(GameObject *go, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });
    virtual weak_ptr<GameObject> GetCollisionObjectPtr(GameObject *go);

    bool PopRequested();
    bool QuitRequested();

    bool isDebug() const;
    void setDebug(bool debug);

    void TestCollision();

    void AddEntitiesFromXML(string xml);

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();
    virtual void IsDeadArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    vector<shared_ptr<GameObject>> objectArray;
    vector<shared_ptr<GameObject>> tileObjectArray;
    vector<shared_ptr<GameObject>> collisionObjectArray;

    bool debug = false;

    void AddEnemy(pugi::xml_node node);

    void AddCrate(string type, int health, Vec2 pos, bool startFalling);
};


#endif //SRC_STATE_H
