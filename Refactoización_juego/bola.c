#include "bola.h"

void ball_init(Ball* ball, float x, float y, float width, float height, float vel_x, float vel_y) {
    ball->entity.x = x;
    ball->entity.y = y;
    ball->entity.width = width;
    ball->entity.height = height;
    ball->entity.vel_x = vel_x;
    ball->entity.vel_y = vel_y;
    ball->entity.is_moving = false;
}

void ball_update(Ball* ball, float delta_time) {
    ball->entity.y += ball->entity.vel_y * delta_time;
}
