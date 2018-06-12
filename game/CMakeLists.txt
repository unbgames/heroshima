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
        include/engine/SDL_include.h
        src/engine/Game.cpp include/engine/Game.h
        src/engine/components/Sprite.cpp include/engine/components/Sprite.h
        src/engine/Music.cpp include/engine/Music.h
        src/engine/Rect.cpp include/engine/Rect.h
        src/engine/Vec2.cpp include/engine/Vec2.h
        src/engine/Component.cpp include/engine/Component.h
        src/engine/GameObject.cpp include/engine/GameObject.h
        src/engine/components/Sound.cpp include/engine/components/Sound.h
        src/engine/TileSet.cpp include/engine/TileSet.h
        src/engine/components/TileMap.cpp include/engine/components/TileMap.h
        src/engine/Resources.cpp include/engine/Resources.h
        src/engine/InputManager.cpp include/engine/InputManager.h
        src/engine/Camera.cpp include/engine/Camera.h
        src/engine/components/CameraFollower.cpp include/engine/components/CameraFollower.h
        src/engine/components/Bullet.cpp include/engine/components/Bullet.h
        include/engine/Collision.h
        src/engine/components/Collider.cpp include/engine/components/Collider.h
        src/util/Timer.cpp include/util/Timer.h
        src/engine/State.cpp include/engine/State.h
        src/state/TitleState.cpp include/state/TitleState.h
        src/engine/components/Text.cpp include/engine/components/Text.h
        src/engine/components/events/PeriodicEvent.cpp include/engine/components/events/PeriodicEvent.h
        src/state/EndState.cpp include/state/EndState.h
        src/engine/GameData.cpp include/engine/GameData.h
        src/state/Menu.cpp include/state/Menu.h
        src/state/Stage1.cpp include/state/Stage1.h
        src/player/Player.cpp include/player/Player.h
        src/engine/components/CollisionTile.cpp include/engine/components/CollisionTile.h
        src/player/PlayerArms.cpp include/player/PlayerArms.h
        include/player/Gun.h src/player/Gun.cpp
        include/player/SpriteSheet.h src/player/SpriteSheet.cpp
        src/util/Structs.cpp include/util/Structs.h
        src/engine/components/animation/Animation.cpp include/engine/components/animation/Animation.h
        src/engine/components/animation/LineTween.cpp include/engine/components/animation/LineTween.h
        src/engine/components/animation/RotationTween.cpp include/engine/components/animation/RotationTween.h
        src/crate/Crate.cpp include/crate/Crate.h
        src/crate/WeaponCrate.cpp include/crate/WeaponCrate.h
        src/crate/LifeCrate.cpp include/crate/LifeCrate.h
        src/engine/components/Gravity.cpp include/engine/components/Gravity.h
        src/menuHUD/Clock.cpp include/menuHUD/Clock.h
        src/menuHUD/MenuHUD.cpp include/menuHUD/MenuHUD.h
        src/engine/components/events/TimerEvent.cpp include/engine/components/events/TimerEvent.h
        src/menuHUD/LifeManager.cpp include/menuHUD/LifeManager.h
        src/menuHUD/GunManager.cpp include/menuHUD/GunManager.h
        src/util/MathUtil.cpp include/util/MathUtil.h
        src/player/BodyState.cpp include/player/BodyState.h
        src/enemy/Enemy.cpp include/enemy/Enemy.h src/enemy/Enemy1.cpp include/enemy/Enemy1.h)

