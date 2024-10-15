#ifndef BOLA_H
#define BOLA_H

#include "Entity.h"

typedef struct {
    Entity entity;
} Ball;

void ball_init(Ball* ball, float x, float y, float width, float height, float vel_x, float vel_y);
void ball_update(Ball* ball, float delta_time);

#endif
