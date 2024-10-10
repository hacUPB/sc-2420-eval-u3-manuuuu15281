#include "Inventario.h"
#include <stdio.h>
#include <stdlib.h>

Inventario* Inventario_crear() {
    Inventario* inv = (Inventario*)malloc(sizeof(Inventario));
    if (!inv) return NULL;
    inv->armas = NULL;
    inv->cantidad_armas = 0;
    return inv;
}

void Inventario_agregar_arma(Inventario* this, Arma* arma) {
    this->armas = realloc(this->armas, sizeof(Arma*) * (this->cantidad_armas + 1));
    this->armas[this->cantidad_armas++] = arma;
}

void Inventario_mostrar(const Inventario* this) {
    printf("Inventario:\\n");
    for (int i = 0; i < this->cantidad_armas; ++i) {
        printf(" - %s (Daño: %d)\\n", this->armas[i]->nombre, this->armas[i]->daño);
    }
}

void Inventario_destruir(Inventario* this) {
    if (this) {
        for (int i = 0; i < this->cantidad_armas; ++i) {
            Arma_destruir(this->armas[i]);
        }
        free(this->armas);
        free(this);
    }
}
