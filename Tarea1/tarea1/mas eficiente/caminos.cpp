/* 5031022 */

/*
  Módulo de implementación de `caminos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/caminos.h"

#include "../include/lista.h"
#include "../include/cola.h"
#include "../include/grafo.h" //si lo saco no pasa nada raro

#include <stdio.h>

#include <cstddef>

nat* CantCaminos(Grafo G, nat s)
{
//en vez de usar cant_vertices usar max_vertice, pues si hay solo 2 vertices pero con nombres 1 y 3 se rompera el arreglo
	nat tamanio = max_vertice(G) + 1;
//	nat tamanio = cantidad_vertices(G) + 1;

	bool* discovered = new bool[tamanio];
	nat* res = new nat[tamanio]; //cantidad de caminos de largo minimo de s a [i]
	nat* distancia_min = new nat[tamanio];

	for (nat i=1; i<tamanio; i++) {	//O(n)
		discovered[i] = false;
//esto es importante porque desde el nodo no habra camino hacia otra componente conexa, y los nodos de esta deberan dar 0
		distancia_min[i] = 0; 
//esto no es estrictamente necesario pues por como esta hecho el algoritmo, solo se pregunta por este dato una vez que fue visitado
//y si fue visitado ya se le seteo dis[padre] + 1. Pero queda bien
		res[i] = 0;
	}

	discovered[s] = true;
	res[s] = 1;
	distancia_min[s] = 0;

	Cola nodos_pendientes = crear_cola();
	encolar(s, nodos_pendientes);
	
	nat nodo_actual;
	nat vecino_actual;
	Lista vecinos;

	while ( !es_vacia_cola(nodos_pendientes) ) {
		nodo_actual = frente(nodos_pendientes);	//O(1)
		desencolar(nodos_pendientes);	//O(1)

		vecinos = adyacentes(nodo_actual, G);	

		while ( !es_vacia_lista(vecinos) ) {	// < O(n)
			vecino_actual = primero(vecinos);	//O(1)
			
			if ( !discovered[vecino_actual] ) {
				discovered[vecino_actual] = true;
				res[vecino_actual] = res[nodo_actual];
				distancia_min[vecino_actual] = distancia_min[nodo_actual] + 1;
				encolar(vecino_actual, nodos_pendientes);	//O(1)
			} else if ( distancia_min[vecino_actual] == distancia_min[nodo_actual] + 1 )
				res[vecino_actual] = res[vecino_actual] + res[nodo_actual];

			vecinos = resto(vecinos); //siempre demora O(1) pues remueve el primer elemento
		}
	}

	delete [] discovered;
	delete [] distancia_min;
	destruir_cola(nodos_pendientes); //O(1) pues la lista sale vacia

	return res;
}
