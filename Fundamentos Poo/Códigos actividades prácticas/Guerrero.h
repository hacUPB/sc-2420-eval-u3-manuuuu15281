#pragma once
#ifndef GUERRERO_H
#define GUERRERO_H

#include "Personaje.h"

typedef struct Guerrero {
    Personaje base;
    int fuerza;
} Guerrero;

Guerrero* Guerrero_crear(const char* nombre, int vida, int nivel, int fuerza);
void Guerrero_destruir(Guerrero* this);


#endif // GUERRERO_H
