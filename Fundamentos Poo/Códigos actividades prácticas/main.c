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
