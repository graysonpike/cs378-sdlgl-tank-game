#include <iostream>

#include "sdlgl/graphics/graphics.h"
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/input/inputs.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>

#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/button.h"
#include "entities/hit_counter.h"


#define KEY_TOGGLE_DEBUG_VISUALS SDL_SCANCODE_GRAVE // Tilde


struct Context {
    Graphics *graphics;
    Scene *scene;
    Scene *menu;
    Scene *pause;
    Scene *win;
    Scene *lose;
    int *game_state;
    Inputs *inputs;
    Clock *clock;
    bool *loop;
};


void game_loop(struct Context context) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen({255, 255, 255, 255});

    if (*(context.game_state) == 0) {
        context.menu->update(context.clock->get_delta());
        context.menu->render();
        if (context.inputs->is_key_down_event(SDL_SCANCODE_RETURN)) {
            *(context.game_state) = 1;
        }
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (context.inputs->is_key_down_event(SDL_SCANCODE_Q)) {
            *context.loop = false;
        }
    }

    else if (*(context.game_state) == 1) {
        context.scene->update(context.clock->get_delta());
        context.scene->render();

        if (context.inputs->is_key_down_event(SDL_SCANCODE_RETURN)) {
            *(context.game_state) = 2;
        }
        // If tilde key is pressed, toggle debug visuals
        if (context.inputs->is_key_down_event(KEY_TOGGLE_DEBUG_VISUALS)) {
            context.graphics->toggle_debug_visuals();
        }
    }

    else if (*context.game_state == 2) {
        context.pause->update(context.clock->get_delta());
        context.scene->render();
        context.pause->render();
        if (context.inputs->is_key_down_event(SDL_SCANCODE_RETURN)) {
            *(context.game_state) = 1;
        }
        if (context.inputs->is_key_down_event(SDL_SCANCODE_Q)) {
            *(context.game_state) = 0;
        }
    }

    else if (*context.game_state == 3) {
        context.win->update(context.clock->get_delta());
        context.win->render();
        if (context.inputs->is_key_down_event(SDL_SCANCODE_RETURN)) {
            *(context.game_state) = 0;
        }
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (context.inputs->is_key_down_event(SDL_SCANCODE_Q)) {
            *(context.game_state) = 0;
        }
    }

    else if (*context.game_state == 4) {
        context.lose->update(context.clock->get_delta());
        context.lose->render();
        if (context.inputs->is_key_down_event(SDL_SCANCODE_RETURN)) {
            *(context.game_state) = 0;
        }
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (context.inputs->is_key_down_event(SDL_SCANCODE_Q)) {
            *(context.game_state) = 0;
        }
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    srand(time(NULL));

    struct Context context;

    context.clock = new Clock();
    context.inputs = new Inputs();
    context.game_state = static_cast<int*>(malloc(sizeof(int)));
    context.loop = static_cast<bool*>(malloc(sizeof(bool)));
    *(context.game_state) = 0;

    // Load a window
    context.graphics = new Graphics(640, 480);

    // Load resources
    context.graphics->get_resources()->load_resources("resources.json");

    // Create and populate scene
    context.scene = new Scene(context.inputs, context.graphics);
    context.menu = new Scene(context.inputs, context.graphics);
    context.pause = new Scene(context.inputs, context.graphics);
    context.win = new Scene(context.inputs, context.graphics);
    context.lose = new Scene(context.inputs, context.graphics);

    // Game entities
    context.scene->add_entity(new Player(context.scene, 100, 280), 1);
    context.scene->add_entity(new Enemy(context.scene, 500, 280), 2);

    context.menu->add_entity(new Button(context.scene, 160, 68, "ui_logo"));
    context.menu->add_entity(new Button(context.scene, 213, 204, "ui_play"));
    context.menu->add_entity(new Button(context.scene, 213, 340, "ui_exit"));

    context.pause->add_entity(new Button(context.scene, 213, 138, "ui_resume"));
    context.pause->add_entity(new Button(context.scene, 213, 274, "ui_exit"));

    context.win->add_entity(new Button(context.scene, 0, 0, "ui_clear"));

    context.lose->add_entity(new Button(context.scene, 0, 0, "ui_lose"));

    // UI entities
    context.scene->add_entity(new FPS_Display(
        context.scene, "base_text", {0, 0, 0, 255}));
    context.scene->add_entity(new EntityCount(
        context.scene, "base_text", {0, 0, 0, 255}));
    HitCounter *hit_counter = new HitCounter(context.scene, "base_text", {0, 0, 0, 255}, "Hits: ", 48);
    HitCounter *damage_counter = new HitCounter(context.scene, "base_text", {0, 0, 0, 255}, "Damage: ", 64);
    context.scene->add_entity(hit_counter, 3);
    context.scene->add_entity(damage_counter, 4);

    *context.loop = true;
    while (*context.loop) {
        if (*context.game_state == 1 && damage_counter->get_count() >= 3) {
            *context.game_state = 4;
        }
        if (*context.game_state == 1 && hit_counter->get_count() >= 2) {
            *context.game_state = 3;
        }
        game_loop(context);

    }

    return 0;
}
