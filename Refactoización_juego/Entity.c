#include "Entity.h"
#include <math.h>

void entity_init(Entity* entity, float x, float y, float width, float height) {
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->vel_x = 0;
    entity->vel_y = 0;
    entity->is_moving = false;
}

bool check_collision(Entity* a, Entity* b) {
    return (a->x < b->x + b->width &&
        a->x + a->width > b->x &&
        a->y < b->y + b->height &&
        a->y + a->height > b->y);
}
