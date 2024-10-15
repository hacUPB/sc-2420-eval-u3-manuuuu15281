#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

typedef struct {
    float x, y;
    float width, height;
    float vel_x, vel_y;
    bool is_moving;
} Entity;

bool check_collision(Entity* a, Entity* b);

#endif
