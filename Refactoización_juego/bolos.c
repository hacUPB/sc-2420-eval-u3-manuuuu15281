#include "bolos.h"

void pin_init(Pin* pin, float x, float y, float width, float height, float vel_x, float vel_y) {
    pin->entity.x = x;
    pin->entity.y = y;
    pin->entity.width = width;
    pin->entity.height = height;
    pin->entity.vel_x = vel_x;
    pin->entity.vel_y = vel_y;
    pin->entity.is_moving = false;
}

void pin_update(Pin* pin, float delta_time) {
    if (pin->entity.is_moving) {
        pin->entity.x += pin->entity.vel_x * delta_time;
        pin->entity.y += pin->entity.vel_y * delta_time;
    }
}
