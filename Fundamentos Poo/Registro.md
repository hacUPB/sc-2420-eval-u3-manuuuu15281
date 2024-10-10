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

#### 2. ENCAPSULAMIENTO
Para esta parte lo único que modifiqué fue la función **mostrar_info_impl** y quedó de la siguiente manera: 
```c
static void mostrar_info_impl(const Arma* this)
{
	printf("Arma: %s | Vida: %d | Nivel: %d\\n", this->nombre, this->daño, this->alcance);
}
```
para este paso aún tengo muchas dudas, comprendí la teoría pero en la ejemplificación no me quedó tan claro.

#### 3.HERENCIA
Para herencia me guié con el ejemplo del profesor, entendí muy bien la teoría y la implementación en el código. Lo único que me gustaría entender mejor es como visualizo en la temrminal las herencias (no sé si me haga entender jejej). Los archivos de Mago me quedaron de la sgte manera: 

**Mago.h**

```c
#pragma once
#ifndef MAGO_H
#define MAGO_H

#include "Personaje.h"

typedef struct Mago {
    Personaje base;//Herencia de Personaje
    int mana;
} Mago;

Mago* Mago_crear(const char* nombre, int vida, int nivel, int mana);
void Mago_destruir(Mago* this);

#endif // !MAGO_H
```

**Mago.c**

```c
#include "Mago.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    Mago* mago = (Mago*)this;
    printf("Mago: %s | Vida: %d | Nivel: %d | Mana: %d\\n", this->nombre, this->vida, this->nivel, mago-> mana);

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
    return nuevo_mago;
}

void Mago_destruir(Mago* this) {
    if (this) {
        //free(this->base.nombre);
        free(this);
    }
}
```
#### 4. POLIMORFISMO
Para los polimorfismos intenté hacer mi actividad práctica y logré que funcionara. Así me quedaron los códigos: 

**Personaje.h**

En este archivo creé la nueva función Atacar.
```c
#ifndef PERSONAJE_H
#define PERSONAJE_H

typedef struct Personaje {
    char nombre [30];
    int vida;
    int nivel;
    void (*mostrar_estado)(const struct Personaje* this);// mostrar estado: método
    void(*atacar)(const struct Personaje* this);//atacar:método
} Personaje;

Personaje* Personaje_crear(const char* nombre, int vida, int nivel); //constructor

void Personaje_destruir(Personaje* this);


char* get_name(Personaje* this); //contiene la info en donde estan los atributos, esta es la firma del get 

#endif // PERSONAJE_H
```

**Mago.c**

Aquí sobrescribí la función atacar.
```c
#include "Mago.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void mostrar_estado_impl(const Personaje* this) {
    Mago* mago = (Mago*)this;
    printf("Mago: %s | Vida: %d | Nivel: %d | Mana: %d\n", this->nombre, this->vida, this->nivel, mago-> mana);

}

 void atacar_mago(const Personaje* this)
{
    Mago* mago = (Mago*)this;
    printf("Mago ataca con una posión \n");
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
```

**Guerrero.c**

Tambien sobrescribí la función atacar.
```c
#include "Guerrero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sobrescribe mostrar_estado de Personaje
static void mostrar_estado_impl(const Personaje* this) {
    Guerrero* guerrero = (Guerrero*)this;
    printf("Guerrero: %s | Vida: %d | Nivel: %d | Fuerza: %d\\n", this->nombre, this->vida, this->nivel, guerrero->fuerza);
}

//sobrescribe atacar
 void atacar_impl(const Personaje* this)
{
    Guerrero* guerrero = (Guerrero*)this; 
    printf("Guerrero %s ataca con fuerza %d\n", this->nombre, guerrero->fuerza);
}

Guerrero* Guerrero_crear(const char* nombre, int vida, int nivel, int fuerza) {
    Guerrero* nuevo_guerrero = (Guerrero*)malloc(sizeof(Guerrero));
    if (!nuevo_guerrero) return NULL;
    //nuevo_guerrero->base.nombre = strdup(nombre);
    strcpy_s(nuevo_guerrero->base.nombre, 30, nombre);
    nuevo_guerrero->base.vida = vida;
    nuevo_guerrero->base.nivel = nivel;
    nuevo_guerrero->fuerza = fuerza;

    nuevo_guerrero->base.mostrar_estado = mostrar_estado_impl;
    nuevo_guerrero->base.atacar = atacar_impl;

    return nuevo_guerrero;
}

void Guerrero_destruir(Guerrero* this) {
    if (this) {
        //free(this->base.nombre);
        free(this);
    }
}
```
Finalmente el main quedó de la sgte manera: 

**main.c**
```c
#include <stdio.h>
#include "personaje.h"
#include "Arma.h"
#include "Guerrero.h"
#include "Mago.h"

int main(void)
{
	Personaje* personajes[2];

	//Personaje* Mago, * Guerrero; //Punteros: donde se guarda un dirección de memoria 
	//Mago= Personaje_crear("GandalF", 3, 10); //Estamos llamando al constructor 


	Guerrero* guerrero = Guerrero_crear("Arthas", 100, 10, 80);
	Mago* mago = Mago_crear("Jaina", 80, 12, 120);

	personajes[0] = (Personaje*)guerrero;
	personajes[1] = (Personaje*)mago;

	//printf("El mago se llama %s\n", Mago->nombre); //Llamamos la instancia Mago->nombre, esto es forma directa y no se debe hacer - %s: significa que voy a imprimir un string

	//printf("El mago se llama %s\n", get_name(Mago)); //Usando el get_name y no la manera directa

	//Personaje_destruir(Mago); //Liberar memoria 
	//Arma* Hacha;
	//Hacha = arma_crear("Hacha", 1, 5);

	//printf("Las caracteristicas de Arma son -> nombre: %s  Dano: %i  Alcance: %i\n", get_namee(Hacha), get_daño(Hacha), get_alcance(Hacha));

	for (int i = 0; i < 2; ++i) {
		personajes[i]->mostrar_estado(personajes[i]);
		personajes[i]->atacar(personajes[i]);
	}

	Guerrero_destruir(guerrero);
	Mago_destruir(mago);

	return 0;
	
}
```

Y en mi terminal se ve así: 
![image](https://github.com/user-attachments/assets/e4dd3d8c-6d41-4060-b5ac-6387b397748a)

#### 5.RELACIÓN ENTRE CLASES



### DISCUSIÓN

**1. ¿Por qué, en este apartado, se afirma que la POO no es un lenguaje de programación? ¿Estás de acuerdo con esta apreciación?**
   
Si estoy de acuerdo con esta afirmación. POO no es un lenguaje sino más bien un paradigma de la programación, lo que quiere decir que es forma o estilo de organizar y estructurar un código. Un lenguaje de programación son las herramientas concretas que se usan para escribir un código. Así que la implementación de la POO depende de un lenguaje de progrmamción. 

**2. ¿Cuál va a ser la estrategia que vas a emplear para modificar tu código, incorporando los conceptos de la POO? Describe el paso a paso**



**4. Deja tus conclusiones luego de esta actividad. ¿Qué aprendiste, qué sabías, pero pudiste profundizar? ¿Cuáles son los temas que aún te generan dudas?**
De esta actividad recordé todo lo que vi el semestre pasado en POO, si bien lo tenía muy fresco lo pude colocar otra vez en práctica pero esta vez en un lenguaje de progrmación diferente. Mi mayor dificultad ha sido acoplarme al lenguaje y como funciona la sintaxis del lenguaje C, aún no lo logro incorporar totalmente y adicional este semestre estoy trabajando con tres lenguajes más en los cuales tambien debo de implementar POO, en conclusión, me confundo constantemente. 
Por último quedé unicamente con dudas en el encapsulamiento, espero que en el refactoring del juego lo pueda aclarar mucho más. 
