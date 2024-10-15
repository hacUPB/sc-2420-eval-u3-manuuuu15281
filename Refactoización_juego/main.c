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
