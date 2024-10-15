#ifndef ARMA_H
#define ARMA_H

typedef struct Arma {
    char nombre[30];
    int daño;
    int alcance;
    void (*mostrar_info)(const struct Arma* this);// mostrar info: método
} Arma;

Arma* arma_crear(const char* nombre, int daño, int alcance);

void Arma_destruir(Arma* this);

char* get_namee(Arma* this);

int* get_daño(Arma* this);

int* get_alcance(Arma* this);

#endif
