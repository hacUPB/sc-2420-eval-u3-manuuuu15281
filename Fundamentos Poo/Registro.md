### ACTIVIDAD 1
#### 1. ABSTRACIÓN
En este primer fundamento comprendí muy bien el ejemplo dado y explicado por el profe. Recordé la creación de clases y entendí muy bien como se implementa en C y el uso de los archivos (.h ) y (.c) . Para la actividad práctica solo se me presentó un problema: no logré imprimir ni el daño ni el alcance, solo el nombre de la arma. Me di cuenta que mi error era nuy simple, no estaba modificando el %s en el printf. Tanto como el daño como el alcance son de tipo int, por lo tanto en el printf debían ir con %i o %d, no con un %s. Luego de caer en cuenta del error lo pude corregir y el codigo funcionó de manera correcta. 

**Arma.h**

```c
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

char* get_daño(Arma* this);

char* get_alcance(Arma* this);

#endif
```

**Arma.c**

```c
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
```

**main.c**

```c
#include <stdio.h>
#include "personaje.h"
#include "Arma.h"

int main(void)
{
	Personaje* Mago, * Guerrero; //Punteros: donde se guarda un dirección de memoria 
	Mago= Personaje_crear("GandalF", 3, 10); //Estamos llamando al constructor 

	//printf("El mago se llama %s\n", Mago->nombre); //Llamamos la instancia Mago->nombre, esto es forma directa y no se debe hacer - %s: significa que voy a imprimir un string

	printf("El mago se llama %s\n", get_name(Mago)); //Usando el get_name y no la manera directa

	Personaje_destruir(Mago); //Liberar memoria 

	Arma* Hacha;
	Hacha = arma_crear("Hacha", 1, 5);

	printf("Las caracteristicas de Arma son -> nombre: %s  Dano: %i  Alcance: %i\n", get_namee(Hacha), get_daño(Hacha), get_alcance(Hacha));
}
```
Finalmente en la **terminal** logré que se vieran así: 
![image](https://github.com/user-attachments/assets/ddc7b6f9-b306-4f7a-889f-85d2a07d4026)



