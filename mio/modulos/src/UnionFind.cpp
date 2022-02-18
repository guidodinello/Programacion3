/* 5031022 */

#include "../include/UnionFind.h"
#include "../include/grafo.h"

#include <stdio.h>

struct elem{
	int size; //tamanio del conjunto
	elem *set_name;
	TNodo element;
};

struct _rep_UnionFind {
	elem* elementos;
	int cardinal;
};


UnionFind MakeUnionFind(TGrafo S){
	UnionFind conjunto = new _rep_UnionFind;
	conjunto -> cardinal = cantidadVertices(S);
	conjunto -> elementos = new elem[cantidadVertices(S)+1]; // el 0 no se usa por comodidad
	for (int i=1; i<int(cantidadVertices(S)); i++){
		conjunto -> elementos[i].size = 1; 
		conjunto -> elementos[i].set_name = NULL;
		conjunto -> elementos[i].element = i;
	}
	return conjunto;
}

static elem* Finding(elem* nodo, UnionFind &conjunto){
printf("nodo.elemento=%i\n",nodo -> element);
	elem* aux = conjunto -> elementos[nodo -> element].set_name;
	if ( aux != NULL) {
		elem* padre = Finding(aux -> set_name, conjunto);
		conjunto -> elementos[nodo -> element].set_name = padre;
		conjunto -> elementos[nodo -> element].size = padre -> size;
	}
	return nodo;
}
TNodo Find(TNodo nodo, UnionFind S){
printf("nodo = %i\n",nodo);
	if (S -> elementos[nodo].set_name == NULL) 
		return nodo; 
	else
		return Finding(S -> elementos[nodo].set_name, S) -> element;
}

void Union(TNodo a, TNodo b, UnionFind S){
	TNodo small = b;
	TNodo big = a;
printf("piola\n");
printf("a = %i\n",a);
	if (S -> elementos[Find(a, S)].size <= S -> elementos[Find(b, S)].size) {
printf("piola2\n");
		small = a;
		big = b;
	}
printf("piola3\n");
printf("menor tamanio = %i\n",S -> elementos[small].element);
	S -> elementos[big].size = S -> elementos[big].size + S -> elementos[small].size;
	S -> elementos[small].size = S -> elementos[big].size;
printf("setname de %i es %i\n", big, S -> elementos[big].set_name -> element);
	S -> elementos[big].set_name = S -> elementos[Find(small, S)].set_name;
}

void showUnionFind(UnionFind S){
	for (int i=1; i <= S -> cardinal; i++)
		printf("nodo %i pertenece a set de %i\n", i, Find(i, S));
	printf("Fin\n");
}
