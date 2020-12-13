#include "hit_counter.h"

#define REFRESH_INTERVAL 0
#define X_COORD 16
#define Y_COORD 48

HitCounter::HitCounter(Scene *scene, std::string font, SDL_Color color, std::string label, int offset)
: Entity(scene), hit_count(0), label(label), offset(offset) {
    this->font = font;
    this->color = color;
}

int HitCounter::get_count() {
    return hit_count;
}

void HitCounter::increment() {
    hit_count ++;
}

void HitCounter::update() {}

void HitCounter::render() {

    if (!scene->get_graphics()->get_debug_visuals_enabled()) {
        return;
    }

    SDL_Texture *text_texture = NULL;
    int texture_width, texture_height;
    
    std::string text = label + std::to_string(hit_count);

    scene->get_graphics()->get_font_renderer()->load_font_texture(
        &text_texture, font, text, color);
    SDL_QueryTexture(text_texture, NULL, NULL, &texture_width, &texture_height);

    SDL_Rect dst = {
        X_COORD,
        offset,
        texture_width,
        texture_height
    };

    SDL_RenderCopy(scene->get_graphics()->get_renderer(), text_texture, NULL, &dst);

    SDL_DestroyTexture(text_texture);
}