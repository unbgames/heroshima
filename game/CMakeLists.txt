cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories(/usr/include/SDL2)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(BEFORE include)
include_directories(BEFORE dep)

add_executable(HEROshima src/Main.cpp
        include/SDL_include.h
        src/engine/Game.cpp include/Game.h
        src/engine/components/Sprite.cpp include/Sprite.h
        src/engine/Music.cpp include/Music.h
        src/engine/Rect.cpp include/Rect.h
        src/engine/Vec2.cpp include/Vec2.h
        src/engine/Component.cpp include/Component.h
        src/engine/GameObject.cpp include/GameObject.h
        src/engine/components/Sound.cpp include/Sound.h
        src/engine/TileSet.cpp include/TileSet.h
        src/engine/components/TileMap.cpp include/TileMap.h
        src/engine/Resources.cpp include/Resources.h
        src/engine/InputManager.cpp include/InputManager.h
        src/engine/Camera.cpp include/Camera.h
        src/engine/components/CameraFollower.cpp include/CameraFollower.h
        src/engine/components/Bullet.cpp include/Bullet.h
        include/Collision.h
        src/engine/components/Collider.cpp include/Collider.h
        src/util/Timer.cpp include/Timer.h
        src/engine/State.cpp include/State.h
        src/state/TitleState.cpp include/TitleState.h
        src/engine/components/Text.cpp include/Text.h
        src/engine/components/events/PeriodicEvent.cpp include/PeriodicEvent.h
        src/state/EndState.cpp include/EndState.h
        src/engine/GameData.cpp include/GameData.h
        src/state/Menu.cpp include/Menu.h
        src/state/Stage1.cpp include/Stage1.h
        src/player/Player.cpp include/Player.h
        src/engine/components/CollisionTile.cpp include/CollisionTile.h
        src/player/PlayerArms.cpp include/PlayerArms.h
        include/Gun.h src/player/Gun.cpp
        include/SpriteSheet.h src/player/SpriteSheet.cpp
        src/util/Structs.cpp include/Structs.h
        src/engine/components/animation/Animation.cpp include/Animation.h
        src/engine/components/animation/LineTween.cpp include/LineTween.h
        src/engine/components/animation/RotationTween.cpp include/RotationTween.h
        src/crate/Crate.cpp include/Crate.h
        src/crate/WeaponCrate.cpp include/WeaponCrate.h
        src/crate/LifeCrate.cpp include/LifeCrate.h
        src/engine/components/Gravity.cpp include/Gravity.h
        src/menuHUD/Clock.cpp include/Clock.h
        src/menuHUD/MenuHUD.cpp include/MenuHUD.h
        src/engine/components/events/TimerEvent.cpp include/TimerEvent.h
        src/menuHUD/LifeManager.cpp include/LifeManager.h
        src/menuHUD/GunManager.cpp include/GunManager.h
        src/util/MathUtil.cpp include/MathUtil.h
        src/enemy/Enemy.cpp include/Enemy.h
        src/enemy/FallingChasingEnemy.cpp include/FallingChasingEnemy.h
        src/enemy/WalkingShootingEnemy.cpp include/WalkingShootingEnemy.h
        src/xml/pugiconfig.hpp src/xml/pugixml.cpp src/xml/pugixml.hpp src/enemy/BigGuy.cpp include/BigGuy.h)

