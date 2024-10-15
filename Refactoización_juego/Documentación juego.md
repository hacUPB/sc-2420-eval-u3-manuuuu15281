# POO aplicado a mi juego: Game Bowling

**PROBLEMAS PRINCIPALES**

- Tenía planeado implementar un power up que estuviese cayendo de la parte superior del juego y que cuando la bola  lo agarrara los bolos aumentaran de tamaño y así fuera más fácil de tumbarlos (el power up duraba 6 seg). Trabajé el último día en este power up pero definitivamente no logré que funcionara mi clase bolos con el nuevo código modificado. Además hacer funcionar el recogible tampocó me funcionó por lo de decidí desistir de este power up por el estrés que me causaba (perdón profe, me rendí).
-  Para esta edición del juego traté de mantener las funcionalidades que ya tenía de la unidad anterior y adaptarlas a POO. Lo que sucedió fue que ahora mis bolos no detectan la colision con las paredes y no supe muy bien como arreglarlo, además mi bola debía reiniciarse apenas era lanzada y salía de la pantalla pero ahora no lo hace.

Al repositorio subí un código funcional pero que carece de ciertas funcionalidades pedidas por el profe.

**DESCRIPCIÓN**

Busco con este ejercicio aplicar toda la teoría vista tanto en clase como en los trabajos autónomos y lograr llevar a cabo mi refactoring de forma correcta y funcional. 

## PASO 1: creación de clases 
En este paso lo que hice fue sacar las clases principales que vi en mi juego y realicé el diagrama de clases de uso UML (muy útil para guiarme cuando estaba haciendo el código).  A continuación una explicación de cada clase creada: 

**Entity:** Esta clase es la base que representa cualquier objeto del juego (bola o bolo) con propiedades de posición, tamaño y velocidad.

**Bola y Bolos:** Heredan de Entity. La bola tiene un método específico lanzar() para lanzarla, mientras que el pin solo tiene su inicialización.

**Game (main):** Gestiona toda la lógica del juego, el renderer, la bola y los bolos. Contiene los métodos principales del juego: inicialización, procesamiento de input, actualización, renderizado y destrucción.

## PASO 2: Reorganización del código 
En este paso lo primero que hice fue configurar el proyecto de visual studio para SDL2, luego creé los siguientes archivos (.h) y (.c): **Entity.h , Entity.c , bolos.h. , bolos.c , bolos.c , bolos.h, main.c** y empecé a darle los diferentes atributos y métodos a cada clase según lo acordado en el diagrama de clases UML. Códigos a continuación: 

**Entity.h**
```c
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
```

**Entity.c**
```c
#include "Entity.h"
#include <math.h>

void entity_init(Entity* entity, float x, float y, float width, float height) { //tengo en duda si dejar esta?????
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
```

**bola.h**
```c
#ifndef BOLA_H
#define BOLA_H

#include "Entity.h"

typedef struct {
    Entity entity;
} Ball;

void ball_init(Ball* ball, float x, float y, float width, float height, float vel_x, float vel_y);
void ball_update(Ball* ball, float delta_time);

#endif
```
**bola.c**
```c
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
```
**bolos.h**
```c
#ifndef BOLOS_H
#define BOLOS_H

#include "Entity.h"

typedef struct {
    Entity entity;
} Pin;

void pin_init(Pin* pin, float x, float y, float width, float height, float vel_x, float vel_y);
void pin_update(Pin* pin, float delta_time);

#endif
```

**bolos.c**
```c
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
```
**constants.h**
```c
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

#endif#pragma once
```
**main.c**
```c
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "bola.h"
#include "bolos.h"
#include "Entity.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool game_is_running = false;
Ball ball;
Pin pins[5]; // 5 bolos
bool ball_launched = false;
float ball_direction = 1.0f; // 1.0 para mover a la derecha, -1.0 para mover a la izquierda
float ball_speed = 200.0f;   // Velocidad lateral de la bola antes de lanzarla


// Inicializar ventana

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow("Bolos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}


// Configuración inicial del juego

void setup(void) {
    // Configurar la bola
    ball_init(&ball, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT - 50, 30, 30, 0, 0);

    // Configurar los bolos (estarán quietos al inicio)
    int pin_spacing = 100;
    for (int i = 0; i < 5; i++) {
        pin_init(&pins[i], 150 + i * pin_spacing, 50, 30, 30, 0, 0);
    }
}


// Procesar input (clic de ratón para lanzar la bola)

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game_is_running = false;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (!ball_launched) {
            ball.entity.vel_y = -300;  // Lanzar la bola hacia arriba
            ball_launched = true;
        }
    }
}


// Actualizar las posiciones de los objetos

void update(float delta_time) {
    if (!ball_launched) {
        // Mover la bola de lado a lado antes de lanzarla
        ball.entity.x += ball_direction * ball_speed * delta_time;

        // Rebotar la bola si llega a los límites de la pantalla
        if (ball.entity.x <= 0) {
            ball.entity.x = 0;
            ball_direction = 1.0f;  // Cambiar la dirección a la derecha
        }
        else if (ball.entity.x + ball.entity.width >= WINDOW_WIDTH) {
            ball.entity.x = WINDOW_WIDTH - ball.entity.width;
            ball_direction = -1.0f;  // Cambiar la dirección a la izquierda
        }
    }
    else {
        // Si la bola fue lanzada, actualizar su movimiento normal
        ball_update(&ball, delta_time);
    }

    // Actualizar los bolos
    for (int i = 0; i < 5; i++) {
        pin_update(&pins[i], delta_time);
        if (check_collision(&ball.entity, &pins[i].entity)) {
            pins[i].entity.vel_x = ball.entity.vel_x * 0.5;
            pins[i].entity.vel_y = ball.entity.vel_y * 0.5;
            pins[i].entity.is_moving = true;
            ball.entity.vel_y = -ball.entity.vel_y;
        }
    }
}


// Renderizar los objetos

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(renderer);

    // Dibujar la bola
    SDL_Rect ball_rect = { (int)ball.entity.x, (int)ball.entity.y, (int)ball.entity.width, (int)ball.entity.height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Bola blanca
    SDL_RenderFillRect(renderer, &ball_rect);

    // Dibujar los bolos
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Bolos rojos
    for (int i = 0; i < 5; i++) {
        SDL_Rect pin_rect = { (int)pins[i].entity.x, (int)pins[i].entity.y, (int)pins[i].entity.width, (int)pins[i].entity.height };
        SDL_RenderFillRect(renderer, &pin_rect);
    }

    SDL_RenderPresent(renderer);
}


// Limpiar y destruir la ventana

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// Función principal

int main(int argc, char* argv[]) {
    game_is_running = initialize_window();

    setup();

    int last_frame_time = 0;

    while (game_is_running) {
        process_input();

        int time_to_wait = 16; // Aproximadamente 60 FPS
        int now = SDL_GetTicks();
        int delta_time = now - last_frame_time;
        if (delta_time < time_to_wait) {
            SDL_Delay(time_to_wait - delta_time);
            continue;
        }
        last_frame_time = now;

        update(delta_time / 1000.0f);  // Convertir a segundos
        render();
    }

    destroy_window();
    return 0;
}

```
En la terminal se ve de la sgte manera: 

![image](https://github.com/user-attachments/assets/9dbd1b3e-33e7-42c4-b8a1-629c8b8f4bd2)

## CONCLUSIÓN

En esta unidad me sentí más cómoda que en la unidad pasada. SDL2 no ha sido mi forma favorita de hacer juegos al ser muy retadora y ambigua, al mismo tiempo he estado tratando de comprenderla mucho más en esta nueva unidad donde le aplicamos POO, la cual ha sido una forma de programar que he trabajado ya en otras materias y me es muy familiar. No logré un código funcional al 100% pero siento que cumplí el obejtivo de esta unidad al comprender como hacer un refactoring y como se aplica POO a un código hecho con C. 
