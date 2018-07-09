//
// Created by edgar on 25/05/18.
//

#include <SpriteSheet.h>

Gun *SpriteSheet::pistol = new Gun(1, -1 /*for infinite ammo*/, 0.5f,
                               StaticSprite("img/hiro/idle_arms.png", 4, 0.3f),
                               StaticSprite("img/hiro/running_arms.png", 8, 0.06f),
                               StaticSprite("img/hiro/shooting_arms.png", 4, 0.1f),
                               StaticSprite("img/hiro/crouch_arms.png", 4, 0.3f, 40),
        Projectile("img/bullet.png", 800, 4, 0.01f));


Gun *SpriteSheet::heavy = new Gun(3, 50, 0.1f,
                              StaticSprite("img/hiro/idle_arms_smg.png", 4, 0.3f),
                              StaticSprite("img/hiro/running_arms_smg.png", 8, 0.06f),
                              StaticSprite("img/hiro/shooting_arms_smg.png", 4, 0.01f),
                              StaticSprite("img/hiro/crouch_arms.png", 4, 0.1f, 40),
        Projectile("img/bullet.png", 1000, 4, 0.01f));

StaticSprite SpriteSheet::idle = StaticSprite("img/hiro/idle.png", 4, 0.3f);

StaticSprite SpriteSheet::walking = StaticSprite("img/hiro/running.png", 8, 0.06f);

StaticSprite SpriteSheet::crouch = StaticSprite("img/hiro/crouch.png", 4, 0.3f);

StaticSprite SpriteSheet::jumping = StaticSprite("img/hiro/jump_up.png", 4, 0.16f);

StaticSprite SpriteSheet::falling = StaticSprite("img/hiro/jump_down.png", 4, 0.1f);

StaticSprite SpriteSheet::landing = StaticSprite("img/hiro/landing.png", 3, 0.04f);

StaticSprite SpriteSheet::soldier = StaticSprite("img/hiro/idle_soldier.png", 4, 0.3f);

StaticSprite SpriteSheet::transformation = StaticSprite("img/hiro/transformation.png", 5, 0.15f);

StaticSprite SpriteSheet::death = StaticSprite("img/hiro/death.png", 8, 0.15f);

StaticSprite SpriteSheet::sword1 = StaticSprite("img/hiro/attack_1.png", 6, 0.05f);

StaticSprite SpriteSheet::sword2 = StaticSprite("img/hiro/attack_2.png", 3, 0.1f);

StaticSprite SpriteSheet::sword3 = StaticSprite("img/hiro/attack_3.png", 5, 0.05f);

StaticSprite SpriteSheet::swordCrouch = StaticSprite("img/hiro/crouch_attack.png", 5, 0.05f);


