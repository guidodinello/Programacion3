/* 5031022 */

/*
  Módulo de implementación de `k_disparos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>

#include "../include/k_disparos.h"

static nat max(int a, int b){
  if (a>b) return a;
  else return b;
}
struct nodo_pila{
  nat dia;
  nodo_pila* abajo;
};
static bool esVacia(nodo_pila* p){
  return p == NULL;
}
static void apilar(nodo_pila* &p, nat d){
  nodo_pila* nuevo = new nodo_pila;
  nuevo -> dia = d;
  nuevo -> abajo = p;
  p = nuevo;
}
static nat desapilar(nodo_pila* &p){
  nodo_pila* aux = p;
  nat res = aux -> dia;
  p = p -> abajo;
  delete aux;
  return res;
}

Estrategia* k_disparos(nat* precios, nat n, nat k)
{
  Estrategia* ret = new Estrategia;
  ret->cant_intervalos = 0;
  ret->intervalos = NULL;
  ret->ganancia_max = 0;

  // Determinar la mejor estrategia

  nat dias = n+1; //en 1 a n dias, [0..n]
  nat parejas = k+1;  //de exactas m parejas, [0..k]
  nat** T = new nat*[parejas];
  for(nat t=0; t<=k; t++){
    T[t] = new nat[dias];
    T[t][1] = 0; // aprovecho e inicializo, en 1 dias no puedo completar ninguna compra-venta
    T[t][0] = 0; // idem 0 dias
  }
  for(nat d=2; d<=n; d++)
    T[0][d] = 0; // con 0 transacciones no puedo generar ganancia 

  /*
    0 1 2 .. n = dias
  0 0 0 0 .. 0
  1 0
  . .
  k 0
  exactamente transacciones
  */
  /*
    i : transaccion
    j : dia
    T[i][j] = max( T[i][j-1], prices[j] + maxDiff )
    maxDiff = max( maxDiff, T[i-1][j] - prices[j] )

    Time : O(kn)
  */

  for(nat t=1; t<=k; t++){
    int maxDiff = -precios[1];
    for(nat d=2; d<=n; d++){
      T[t][d] = max( T[t][d-1], precios[d] + maxDiff );
      maxDiff = max( maxDiff, T[t-1][d] - precios[d] ); //aca seria T[t-1][d-1] ??
    }
  }

  ret -> ganancia_max = T[k][n] * 1000;


  // Estrategia

  int t=k;
  int d=n;
  nat aux;
  int maxDiff;
  nat tamanio_pila = 0;
  nodo_pila* pila = NULL;
  while (true){
    if (t == 0 || d == 0){
      break;
    }
    if (T[t][d] == T[t][d-1]){
      d = d-1;
    } else {
      apilar(pila, d);
      tamanio_pila ++;
      maxDiff = T[t][d] - precios[d];
      for(int iter_dias=1; iter_dias<d; iter_dias++){
        aux = T[t-1][iter_dias] - precios[iter_dias];
        if ( int(aux) == maxDiff){
          t = t-1;
          d = iter_dias;
          apilar(pila, d);
          tamanio_pila ++;
          break;
        }
      } 
    }
  }


  ret -> cant_intervalos = tamanio_pila/2;
  ret -> intervalos = new Intervalo[tamanio_pila];
  nat indice = 0;
  nat compra, venta;
  while (!esVacia(pila)){
    compra = desapilar(pila);
    ret -> intervalos[indice].inicio = compra;
    venta = desapilar(pila);
    ret -> intervalos[indice].fin = venta;
    indice ++;
  }
/*  IMPRIMIR MATRIZ
   for(nat i=0; i<=k; i++){
     for(nat j=0; j<=n; j++)
        printf("%i   ",T[i][j]);
      printf("\n");
    }
*/
  for(nat i=0; i<=k; i++)
    delete [] T[i];
  delete [] T;

  return ret;
}
