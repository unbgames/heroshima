//
// Created by edgar on 25/05/18.
//

#include <Guns.h>

Gun *Guns::pistol = new Gun(20, 20, 0.5f,
        Sprites("img/tarma_superior_repouso.png", 10, 4, 0.5f),
        Sprites("img/tarma_superior_andando.png", 30, 12, 0.4f),
        Sprites("img/tarma_superior_atirando.png", 30, 10, 0.4f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));


Gun *Guns::heavy = new Gun(50, 100, 0.01f,
                            Sprites("img/tarma_heavy_rest.png", 20, 4, 0.5f),
                            Sprites("img/tarma_heavy_walk.png", 30, 12, 0.4f),
                            Sprites("img/tarma_heavy_shoot.png", 35, 4, 0.4f),
                            Projectile("img/minionbullet2.png", 700, 3, 0.01f));

//Gun *Guns::heavy = new Gun(20, 100, "img/tarma_heavy_shoot.png", 40, 4, 0.4f, 0.01f, 900, 3, 0.01);
