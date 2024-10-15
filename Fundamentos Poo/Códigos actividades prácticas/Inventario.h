#pragma once
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Arma.h"

typedef struct Inventario {
    Arma** armas;
    int cantidad_armas;
} Inventario;

Inventario* Inventario_crear();
void Inventario_agregar_arma(Inventario* this, Arma* arma);
void Inventario_mostrar(const Inventario* this);
void Inventario_destruir(Inventario* this);

#endif // INVENTARIO_H
