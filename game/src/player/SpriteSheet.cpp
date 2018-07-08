//
// Created by edgar on 25/05/18.
//

#include <SpriteSheet.h>

Gun *SpriteSheet::pistol = new Gun(1, -1 /*for infinite ammo*/, 0.5f,
                               StaticSprite("img/hiro/idle_arms.png", 4, 0.3f),
                               StaticSprite("img/hiro/running_arms.png", 8, 0.06f),
                               StaticSprite("img/hiro/shooting_arms.png", 4, 0.1f),
                               StaticSprite("img/hiro/crouch_arms.png", 4, 0.3f, 40),
        Projectile("img/bullet.png", 1000, 4, 0.01f));


Gun *SpriteSheet::heavy = new Gun(3, 100, 0.1f,
                              StaticSprite("img/tarma_heavy_rest.png", 4, 0.3f, 20),
                              StaticSprite("img/tarma_heavy_walk.png", 12, 1.0f, 30),
                              StaticSprite("img/tarma_heavy_shoot.png", 4, 0.02f, 38),
                              StaticSprite("img/crouch_arms.png", 4, 0.1f, 40),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));

StaticSprite SpriteSheet::idle = StaticSprite("img/hiro/idle.png", 4, 0.3f);

StaticSprite SpriteSheet::walking = StaticSprite("img/hiro/running.png", 8, 0.06f);

StaticSprite SpriteSheet::crouch = StaticSprite("img/hiro/crouch.png", 4, 0.3f);

StaticSprite SpriteSheet::jumping = StaticSprite("img/hiro/jump_up.png", 4, 0.16f);

StaticSprite SpriteSheet::falling = StaticSprite("img/hiro/jump_down.png", 4, 0.1f);

StaticSprite SpriteSheet::landing = StaticSprite("img/hiro/landing.png", 3, 0.04f);

StaticSprite SpriteSheet::transformation = StaticSprite("img/hiro/transformation.png", 5, 0.15f);

