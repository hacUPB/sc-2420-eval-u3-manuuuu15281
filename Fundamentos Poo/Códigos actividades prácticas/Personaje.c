#include "Personaje.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    printf("Personaje: %s | Vida: %d | Nivel: %d\\n", this->nombre, this->vida, this->nivel);
}

static void atacar_impl(const Personaje* this) {
    printf("%s ataca con %s causando %d de daño.\\n", this->nombre, this->arma->nombre, this->arma->daño);
}

Personaje* Personaje_crear(const char* nombre, int vida, int nivel) { //constructor 
    Personaje* nuevo_personaje = (Personaje*)malloc(sizeof(Personaje)); //Aquí creamos un puntero dinamico - malloc : reserva bytes en la ram 
    if (!nuevo_personaje) return NULL;
    //nuevo_personaje->nombre = strdup(nombre);
    strcpy_s(nuevo_personaje->nombre, 30, nombre);
    nuevo_personaje->vida = vida;
    nuevo_personaje->nivel = nivel;

    nuevo_personaje->mostrar_estado = mostrar_estado_impl;
    nuevo_personaje->atacar = atacar_impl;

    return nuevo_personaje;
}


char* get_name(Personaje* this) //implementación del get 
{
    return this->nombre; 
}

void Personaje_destruir(Personaje* this) {
    if (this) {
        //free(this->nombre); //free es la función que libera la memoria usada 
        free(this);
    }
}
