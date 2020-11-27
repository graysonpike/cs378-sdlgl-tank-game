#ifndef TANK_H
#define TANK_H

#include <SDL2/SDL.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/game/physical_entity.h>
#include <sdlgl/game/timer.h>
#include <sdlgl/graphics/texture.h>

class Tank : public PhysicalEntity {

    std::map<std::string, Texture> textures;
    Sound fire_sound;
    Timer reload_timer = Timer(3.0f);
    Timer recoil_timer = Timer(1.0f);
    float turret_angle = 0.0f;
    float hull_angle = 0.0f;
    float driving_speed = 40.0f;
    float turning_speed = 30.0f;
    float turret_speed = 30.0f;
    static const int gun_recoil_amount = 10;
    static const int turret_offset = 0;
    static const int barrel_offset = 40;

public:

    Tank(Scene *scene, float x, float y);
    void update();
    void render();

    void drive(bool direction, bool turn_left, bool turn_right);
    void rotate_turret(bool direction);
    void fire();

};

#endif