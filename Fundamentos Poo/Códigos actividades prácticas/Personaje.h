#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Arma.h"

typedef struct Personaje {
    char nombre [30];
    int vida;
    int nivel;
    Arma* arma;
    void (*mostrar_estado)(const struct Personaje* this);// mostrar estado: método
    void(*atacar)(const struct Personaje* this);//atacar:método
} Personaje;




Personaje* Personaje_crear(const char* nombre, int vida, int nivel); //constructor

void Personaje_destruir(Personaje* this);


char* get_name(Personaje* this); //contiene la info en donde estan los atributos, esta es la firma del get 

#endif // PERSONAJE_H 
