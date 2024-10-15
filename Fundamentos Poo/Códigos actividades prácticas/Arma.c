#include "Arma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_info_impl(const Arma* this)
{
	printf("Arma: %s | Vida: %d | Nivel: %d\\n", this->nombre, this->daño, this->alcance);
}

Arma* arma_crear(const char* nombre, int daño, int alcance)
{
    Arma* nuevo_arma = (Arma*)malloc(sizeof(Arma)); //Aquí creamos un puntero dinamico - malloc : reserva bytes en la ram 
    if (!nuevo_arma) return NULL;
    //nuevo_personaje->nombre = strdup(nombre);
    strcpy_s(nuevo_arma->nombre, 30, nombre);
    nuevo_arma->daño = daño;
    nuevo_arma->alcance = alcance;
    nuevo_arma->mostrar_info = mostrar_info_impl;
    return nuevo_arma;

}

char* get_namee(Arma* this) //implementación del get 
{
    return this->nombre;
}

int* get_daño(Arma* this) //implementación del get 
{
    return this->daño;
}

int* get_alcance(Arma* this) //implementación del get 
{
    return this->alcance;
}

// Función para destruir el objeto Arma y liberar memoria
void Arma_destruir(Arma* this) {
    if (this) {
        //free(this->nombre);  // Libera la memoria del nombre
        free(this);  // Libera la estructura
    }
}
