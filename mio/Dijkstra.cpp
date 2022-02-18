#include <stdio.h>

void chequeo(){
	printf("bien\n");
}

struct nodo_cola{
	int vertice;
	nodo_cola *sig;
};
struct rep_cola{
	nodo_cola *primero;
	nodo_cola *ultimo;
};
typedef rep_cola *Cola;

struct rep_pila{
	nodo_cola *cima;
};
typedef rep_pila *Pila;

Pila crearPila(){
	Pila nueva = new rep_pila;
	nueva -> cima = NULL;
	return nueva;
}
bool pilaVacia(Pila p){
	return p -> cima == NULL;
}
void apilar(Pila &p, int v){
	nodo_cola* nuevo = new nodo_cola;
	nuevo -> vertice = v;
	nuevo -> sig = p -> cima;
	p -> cima = nuevo;
}
void desapilar(Pila &p){
	nodo_cola* aux = p -> cima;
	p -> cima = p -> cima -> sig;
	delete aux;
}
int tope(Pila p){
	return p -> cima -> vertice;
}
void mostrarPila(Pila p){
	printf("Pila : ");
	while (!pilaVacia(p)){
		printf("%i ",tope(p));
		desapilar(p);
	}
	printf(" . \n");
}

Cola crearCola(){
	Cola nueva = new rep_cola;
	nueva -> primero = nueva -> ultimo = NULL;
	return nueva;
}
void mostrarCola(Cola c){//desencolo del primero
	nodo_cola* iter = c -> primero;
	printf("Cola : ");
	while (iter != NULL){
		printf("%i ",iter -> vertice);
		iter = iter -> sig;
	}
	printf(" . \n");
}
bool colaVacia(Cola c){
	return c -> primero == NULL;
}
void encolar(Cola &c, int v){
	nodo_cola* nuevo = new nodo_cola;
	nuevo -> vertice = v;
	nuevo -> sig = c -> primero;
	c -> primero = nuevo;
	if (nuevo -> sig == NULL) c -> ultimo = nuevo;
}
void desencolar(Cola &c){
	nodo_cola* aux = c -> primero;
	c -> primero = c -> primero -> sig;
	delete aux;
}
int frenteCola(Cola c){
	return c -> primero -> vertice;
}

struct nodo_lista{
	int vertice;
	int ponderacion;
	nodo_lista *sig;
};
typedef nodo_lista *Lista;

struct rep_grafo{
	int cant_vertices;
	Lista* vertice;
};
typedef rep_grafo *Grafo;

Lista crearLista(){
	return NULL;
}
void mostrarLista(Lista l){
	printf("Lista : ");
	nodo_lista* iter = l;
	while (iter != NULL){
		printf("(%i,p=%i) ", iter -> vertice, iter -> ponderacion);
		iter = iter -> sig;
	}
	printf(" . \n");
}

Grafo crearGrafo(int n){
	Grafo nuevo = new rep_grafo;
	nuevo -> cant_vertices = n;
	nuevo -> vertice = new Lista[n+1];
	for (int i=1;i<n; i++) nuevo -> vertice[i] = crearLista();
	return nuevo;
}

void agregarArista(Grafo &G, int coste, int vertice, int adyacente){
	nodo_lista* nuevo = new nodo_lista;
	nuevo -> vertice = adyacente;
	nuevo -> ponderacion = coste;
	nuevo -> sig = G -> vertice[vertice]; 
	G -> vertice[vertice] = nuevo;

	nodo_lista* nuevo2 = new nodo_lista;
	nuevo2 -> vertice = vertice;
	nuevo2 -> ponderacion = coste;
	nuevo2 -> sig = G -> vertice[adyacente];
	G -> vertice[adyacente] = nuevo2;
}

struct rep_conjaris{
	int vertice1;
	int vertice2;
	rep_conjaris *ant;
};
typedef rep_conjaris *ConjAris;

ConjAris crearConjAris(){
	return NULL;
}
void mostrarConjAris(ConjAris conja){
	printf("Conjunto de Aristas : ");
	ConjAris iter = conja;
	while (iter != NULL){
		printf("(%i,%i) ",iter -> vertice1, iter -> vertice2);
		iter = iter -> ant;
	}
	printf(" . \n");
}
void agregarConjAris(ConjAris &conja, int v1, int v2){
	ConjAris nuevo = new rep_conjaris;
	nuevo -> vertice1 = v1;
	nuevo -> vertice2 = v2;

	nuevo -> ant = conja;
	conja = nuevo;
}
Pila ConjArisAPila(ConjAris conja){
	Pila res = crearPila();

	ConjAris iter = conja;

	mostrarConjAris(conja);

	apilar(res, iter -> vertice2);
	apilar(res, iter -> vertice1);
	iter = iter -> ant;
	while (iter != NULL){
		if (iter -> vertice2 == tope(res)) apilar(res, iter -> vertice1);
		iter = iter -> ant;
	}
	return res;
}

struct rep_Dijkstra{
	int* distancias;
	ConjAris recorrido;
};
typedef rep_Dijkstra *resD;

resD Dijkstra(Grafo G, int principio){
	resD resultado = new rep_Dijkstra;
	resultado -> distancias = new int[G -> cant_vertices + 1];
	resultado -> recorrido = crearConjAris();

	resultado -> distancias[principio] = 0;
	Cola VmenosS = crearCola();
	Cola S = crearCola();
	encolar(S, principio);

	bool* explorado = new bool[G -> cant_vertices + 1];
	for (int i=G -> cant_vertices; i>0; i--) {
		if (i != principio) {
			encolar(VmenosS, i);
			explorado[i] = false;
		} else explorado[i] = true;
	}

	int num,enS,min;
	nodo_lista* iter;
	while (!colaVacia(VmenosS)){	//minetras s distinto de v
		min = 1000;
		num = frenteCola(VmenosS);	//agarro un nodo que no este en s
		iter = G -> vertice[num];
		printf("Selecciono de V-S a num=%i \n",num);
		while ( iter != NULL){	//busco en los vecinos de num, alguno que este en S
			printf("vecino de num %i\n",iter->vertice);
			if (explorado[iter -> vertice] == true){	//si esta en S veo si es la menor
				printf("esta en S %i\n",iter->vertice);
				if (iter -> ponderacion < min) {
					printf("iter->ponderacion=%i < min=%i\n",iter->ponderacion,min);
					min = iter -> ponderacion;
					enS = iter -> vertice;
					printf("enS=%i\n",enS);
				}
			}
			iter = iter -> sig;
		}
		agregarConjAris(resultado -> recorrido, enS, num);
		resultado -> distancias[num] = min + resultado -> distancias[enS];
		printf("desencolado=%i\n",frenteCola(VmenosS));
		desencolar(VmenosS);
		explorado[num] = true;
	}
	printf("dijkstra");
	return resultado;
}

void mostrarGrafo(Grafo g){
	for (int i=1; i<=g -> cant_vertices; i++){
		printf("Nodo %i : ",i);
		mostrarLista(g -> vertice[i]);
	}
}

int main(){
	int puntos = 6;
	Grafo Mapa = crearGrafo(puntos);

	//Construir grafo
	agregarArista(Mapa,5,1,5);
	agregarArista(Mapa,6,1,2);
	agregarArista(Mapa,7,5,2);
	agregarArista(Mapa,8,5,3);
	agregarArista(Mapa,1,2,3);
	agregarArista(Mapa,9,4,3);
	agregarArista(Mapa,4,5,4);
	agregarArista(Mapa,2,3,6);
	agregarArista(Mapa,3,4,6);
	//
	mostrarGrafo(Mapa);
	int origen = 1;
	resD resultado = Dijkstra(Mapa, origen);

	chequeo();
	mostrarPila(ConjArisAPila(resultado -> recorrido));
}
