#include <stdio.h>

#define Size 6; //el valor real sera size -1

struct nodo_solucion{
    int id_m;
    int id_w;
    solucion* sig;
};

struct nodo_solucion* solucion;

solucion crearSol(){
    return NULL;
}

void agregar(solucion &s, int m, int w){
    nodo_solucion* nuevo = new nodo_solucion;
    nuevo -> id_m = m;
    nuevo -> id_w = w;
    nuevo -> sig = NULL;

    if (s -> fin == NULL) s -> inicio = nuevo;
    else s -> fin -> sig = nuevo;
    s -> fin = nuevo;
}

void mostrarSol(solucion h){
    solucion s = h;
    printf("Solucion : ");
    while (s != NULL) {
        printf("(M%i,W%i)",s -> id_m, s -> id_w);
        s = s -> sig;
    }
    printf(".\n");
}
//--------------------------------------------//

struct rep_conjunto{
    char name;
    int* id;
    int* pref;
    int iter;
    int pref_iter;
};

typedef rep_conjunto* conjunto; 

conjunto crearConjunto(char c, int S, int* preferencias){
    rep_conjunto* nuevo = new rep_conjunto;
    nuevo -> name = c;
    nuevo -> id = new int[S];
    nuevo -> pref;
    int v;
    for (int i=1; i<S; i++) nuevo -> id[i] = i;
    nuevo -> pref = preferencias;
    nuevo -> id[0] = Size - 1;
    nuevo -> iter = nuevo -> pref_iter = 1;
    return nuevo;
}

void moverIter(conjunto &S, char c){
    if (c == 'p') S -> pref_iter ++;
    else if (c == 'c') S -> iter ++;
}

conjunto GaleShapley(conjunto m, conjunto w){
    solucion sol = crearSol();

    while(m -> id[0] != 0){


        agregar(S, m -> id[m -> iter], m -> pref[m -> iter]);
        moverIter(m, c);
        m -> id[0] --;
    }

    return sol;
}

int main(){


}