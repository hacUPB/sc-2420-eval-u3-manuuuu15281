#ifndef BOLOS_H
#define BOLOS_H

#include "Entity.h"

typedef struct {
    Entity entity;
} Pin;

void pin_init(Pin* pin, float x, float y, float width, float height, float vel_x, float vel_y);
void pin_update(Pin* pin, float delta_time);

#endif
