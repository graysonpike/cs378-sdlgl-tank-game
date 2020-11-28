#ifndef TANK_H
#define TANK_H

#include <SDL2/SDL.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/game/physical_entity.h>
#include <sdlgl/game/timer.h>
#include <sdlgl/graphics/texture.h>


class Tank : public PhysicalEntity {

    enum DrivingState {
        NOT_DRIVING,
        FORWARD,
        BACKWARD
    };

    enum TurningState {
        NOT_TURNING,
        LEFT,
        RIGHT
    };

    static const float forward_driving_speed;
    static const float stationary_turn_forward_speed;
    static const float backward_driving_speed;
    static const float turning_speed;
    static const float turret_speed;
    static const int gun_recoil_amount;
    static const int turret_offset;
    static const int barrel_offset;

    std::map<std::string, Texture> textures;
    Sound fire_sound;
    Timer reload_timer = Timer(3.0f);
    Timer recoil_timer = Timer(1.0f);
    float turret_angle = 0.0f;
    float hull_angle = 0.0f;
    DrivingState driving_state = DrivingState::NOT_DRIVING;
    TurningState turning_state = TurningState::NOT_TURNING;

    void move();

public:

    Tank(Scene *scene, float x, float y);
    void update();
    void render();

    void drive(bool direction);
    void turn(bool direction);
    void rotate_turret(bool direction);
    void fire();

};

#endif