#include "Mago.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    Mago* mago = (Mago*)this;
    printf("Mago: %s | Vida: %d | Nivel: %d | Mana: %d\\n", this->nombre, this->vida, this->nivel, mago-> mana);

}

 void atacar_mago(const Personaje* this)
{
    Mago* mago = (Mago*)this;
    printf("Mago ataca con una posion\n");
}

Mago* Mago_crear(const char* nombre, int vida, int nivel, int mana) {
    Mago* nuevo_mago = (Mago*)malloc(sizeof(Mago));
    if (!nuevo_mago) return NULL;
    //nuevo_guerrero->base.nombre = strdup(nombre);
    strcpy_s(nuevo_mago->base.nombre, 30, nombre);
    nuevo_mago->base.vida = vida;
    nuevo_mago->base.nivel = nivel;
    nuevo_mago->mana = mana;

    nuevo_mago->base.mostrar_estado = mostrar_estado_impl;
    nuevo_mago->base.atacar = atacar_mago;

    return nuevo_mago;
}

void Mago_destruir(Mago* this) {
    if (this) {
        //free(this->base.nombre);
        free(this);
    }
}

