//
// Created by edgar on 25/05/18.
//

#ifndef GUN_H
#define GUN_H

#include <string>

using std::string;

class Gun {
public:
    Gun();

    Gun(int damage, int ammo, string sprite, int spriteOffset, int spriteFrameCount, float spriteFrameTime,
        float cooldownTime, float projectileSpeed, int projectileFrameCount, float projectileFrameTime);

    int getDamage() const;
    int getAmmo() const;

    const string &getSprite() const;
    int getSpriteOffset() const;
    int getSpriteFrameCount() const;
    float getSpriteFrameTime() const;

    float getCooldownTime() const;
    float getProjectileSpeed() const;
    int getProjectileFrameCount() const;
    float getProjectileFrameTime() const;

    void decrementAmmo();

private:
    int damage;
    int ammo;

    string sprite;
    int spriteOffset;
    int spriteFrameCount;
    float spriteFrameTime;

    float cooldownTime;
    float projectileSpeed;
    int projectileFrameCount;
    float projectileFrameTime;

};


#endif //SRC_GUN_H
