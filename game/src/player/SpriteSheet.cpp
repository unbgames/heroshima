//
// Created by edgar on 25/05/18.
//

#include <SpriteSheet.h>

Gun *SpriteSheet::pistol = new Gun(1, -1 /*for infinite ammo*/, 0.5f,
                               StaticSprite("img/idle_arms.png", 4, 0.3f),
                               StaticSprite("img/running_arms.png", 8, 0.06f),
                               StaticSprite("img/shooting_arms.png", 4, 0.1f),
                               StaticSprite("img/crouch_arms.png", 4, 0.3f, 30),
        Projectile("img/bullet.png", 700, 4, 0.01f));


Gun *SpriteSheet::heavy = new Gun(3, 300, 0.1f,
                              StaticSprite("img/tarma_heavy_rest.png", 4, 0.3f, 20),
                              StaticSprite("img/tarma_heavy_walk.png", 12, 1.0f, 30),
                              StaticSprite("img/tarma_heavy_shoot.png", 4, 0.02f, 38),
                              StaticSprite("img/crouch_arms.png", 4, 0.1f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));

StaticSprite SpriteSheet::idle = StaticSprite("img/idle.png", 4, 0.3f);

StaticSprite SpriteSheet::walking = StaticSprite("img/running.png", 8, 0.06f);

StaticSprite SpriteSheet::crouch = StaticSprite("img/crouch.png", 4, 0.3f);

StaticSprite SpriteSheet::jumping = StaticSprite("img/jumping_up.png", 4, 0.1f);

StaticSprite SpriteSheet::falling = StaticSprite("img/falling.png", 7, 0.1f);
